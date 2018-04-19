/*******************************************************************************
* Assignment: Project 2 - Syntactic Analyzer for Scheme to C++ Translator      *
* Author:                                                                      *
* Date: Spring 2018                                                            *
* File: SyntacticalAnalyzer.cpp                                                *
*                                                                              *
* Description: This file contains the                                          *
*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>

#include "SyntacticalAnalyzer.h"

using namespace std;

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
SyntacticalAnalyzer::SyntacticalAnalyzer(char * filename)
{
    lex = new LexicalAnalyzer(filename);
    string name = filename;
    string p2name = name.substr(0, name.length()-3) + ".p2";
    p2file.open (p2name.c_str());
    token = lex->GetToken();
    Program();
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
SyntacticalAnalyzer::~SyntacticalAnalyzer()
{
    delete lex;
    p2file.close();
}


typedef char rule;
enum { NoRule = 0 };

enum non_terminal {
    ntProgram, ntDefine, ntMoreDefines, ntStmtList, ntStmt, ntLiteral,
    ntQuotedLit, ntMoreTokens, ntParamList, ntElsePart, ntStmtPair,
    ntStmtPairBody, ntAction, ntAnyOtherToken
};

rule checkRule(non_terminal nt, token_type token)
{
#include "syntaxrules.hpp"

    if (token <= NONE || token >= MAX_TOKENS)
        return NoRule;

    return rules[nt][token];
}


#define USING_RULE(rule) \
    do { p2file << "Using rule " << static_cast<int>(rule) << endl; } while (0)
#define REPORT_MISSING(expected) \
    do { lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; " \
                          "expected " + (expected)); } while (0)
#define USING_FUNCTION(funcName) \
    do { p2file << "Entering " << funcName << " function; current token is: " \
                << lex->GetTokenName(token) << endl; } while (0)
#define FUNCTION_EXIT(funcName)                                         \
    do { p2file << "Exiting " << funcName << " function; current token is: " \
                << lex->GetTokenName(token) << endl; } while (0)

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::Program()
{
    int errors = 0;

    // token should be in firsts of Program

    rule const r = checkRule(ntProgram, token);
    USING_FUNCTION("Program");
    if (r != NoRule) {
        USING_RULE(r);
        errors += Define();
        errors += MoreDefines();
        if (token != EOF_T) {
            REPORT_MISSING("end of file");
            ++errors;
        }
    }
    else {
        REPORT_MISSING("a program"); // TODO: expected what?
        ++errors;
    }

    // token should be in follows of Program

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::Define()
{
    int errors = 0;

    rule const r = checkRule(ntDefine, token);
    USING_FUNCTION("Define");
    if (r != NoRule) {
        USING_RULE(r);
        token = lex->GetToken();
    }
    else {
        REPORT_MISSING("'('");
        ++errors;
    }

    if (token == DEFINE_T) {
        token = lex->GetToken();
    }
    else {
        REPORT_MISSING("'define'");
        ++errors;
    }

    if (token == LPAREN_T) {
        token = lex->GetToken();
    }
    else {
        REPORT_MISSING("'('");
        ++errors;
    }

    if (token == IDENT_T) {
        token = lex->GetToken();
    }
    else {
        REPORT_MISSING("an identifier");
        ++errors;
    }

    errors += ParamList();

    if (token == RPAREN_T) {
        token = lex->GetToken();
    }
    else {
        REPORT_MISSING("')'");
        ++errors;
    }

    errors += Stmt();
    errors += StmtList();

    if (token == RPAREN_T) {
        token = lex->GetToken();
    }
    else {
        REPORT_MISSING("')'");
        ++errors;
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::MoreDefines()
{
    int errors = 0;

    rule const r = checkRule(ntMoreDefines, token);
    USING_FUNCTION("MoreDefines");
    switch (r) {
    case 3:
        USING_RULE(r);
        errors += Define();
        errors += MoreDefines();
        break;
    case 4:
        USING_RULE(r);
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::MoreDefines()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::StmtList()
{
    int errors = 0;

    rule const r = checkRule(ntStmtList, token);
    USING_FUNCTION("StmtList");
    switch (r) {
    case 5:
        USING_RULE(r);
        errors += Stmt();
        errors += StmtList();
        break;
    case 6:
        USING_RULE(r);
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::StmtList()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::Stmt()
{
    int errors = 0;

    rule const r = checkRule(ntStmt, token);
    USING_FUNCTION("Stmt");
    switch (r) {
    case 7:
        USING_RULE(r);
        errors += Literal();
        break;
    case 8:
        USING_RULE(r);
        token = lex->GetToken();
        break;
    case 9:
        USING_RULE(r);
        token = lex->GetToken();
        errors += Action();
        if (token == RPAREN_T) {
            token = lex->GetToken();
        }
        else {
            REPORT_MISSING("')'");
            ++errors;
        }
        break;
    case NoRule:
        REPORT_MISSING("'('");
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Stmt()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::Literal()
{
    int errors = 0;

    rule const r = checkRule(ntLiteral, token);
    USING_FUNCTION("Literal");
    switch (r) {
    case 10:
    case 11:
        USING_RULE(r);
        token = lex->GetToken();
        break;
    case 12:
        USING_RULE(r);
        token = lex->GetToken();
        errors += QuotedLit();
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Literal()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::QuotedLit()
{
    int errors = 0;

    rule const r = checkRule(ntQuotedLit, token);
    USING_FUNCTION("QuotedLit");
    if (r != NoRule) {
        USING_RULE(r);
        errors += AnyOtherToken();
    }
    else {
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::MoreTokens()
{
    int errors = 0;

    rule const r = checkRule(ntMoreTokens, token);
    USING_FUNCTION("MoreTokens");
    switch (r) {
    case 14:
        USING_RULE(r);
        errors += AnyOtherToken();
        errors += MoreTokens();
        break;
    case 15:
        USING_RULE(r);
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::MoreTokens()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::ParamList()
{
    int errors = 0;

    rule const r = checkRule(ntParamList, token);
        USING_FUNCTION("ParamList");
    switch (r) {
    case 16:
        USING_RULE(r);
        token = lex->GetToken();
        errors += ParamList();
        break;
    case 17:
        USING_RULE(r);
        break;
    case NoRule:
        REPORT_MISSING("an identifier or ')'"); // TODO: verify expected
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::ParamList()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::ElsePart()
{
    int errors = 0;

    rule const r = checkRule(ntElsePart, token);
    USING_FUNCTION("ElsePart");
    switch (r) {
    case 18:
        USING_RULE(r);
        errors += Stmt();
        break;
    case 19:
        USING_RULE(r);
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::ElsePart()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::StmtPair()
{
    int errors = 0;

    rule const r = checkRule(ntStmtPair, token);
    USING_FUNCTION("StmtPair");
    switch (r) {
    case 20:
        USING_RULE(r);
        token = lex->GetToken();
        errors += StmtPairBody();
        break;
    case 21:
        USING_RULE(r);
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::StmtPair()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::StmtPairBody()
{
    int errors = 0;

    rule const r = checkRule(ntStmtPairBody, token);
    USING_FUNCTION("StmtPairBody");
    switch (r) {
    case 22:
        USING_RULE(r);
        errors += Stmt();
        errors += Stmt();
        if (token == RPAREN_T) {
            token = lex->GetToken();
        }
        else {
            REPORT_MISSING("')'");
            ++errors;
        }
        errors += StmtPair();
        break;
    case 23:
        USING_RULE(r);
        token = lex->GetToken();
        errors += Stmt();
        if (token == RPAREN_T) {
            token = lex->GetToken();
        }
        else {
            REPORT_MISSING("')'");
            ++errors;
        }
        break;
    case NoRule:
        REPORT_MISSING("something else'"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::StmtPairBody()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::Action()
{
    int errors = 0;

    rule const r = checkRule(ntAction, token);
    USING_FUNCTION("Action");
    switch (r) {
    case 24:
        USING_RULE(r);
        token = lex->GetToken();
        errors += Stmt();
        errors += Stmt();
        errors += ElsePart();
        break;
    case 25:
        USING_RULE(r);
        token = lex->GetToken();
        if (token == LPAREN_T) {
            token = lex->GetToken();
        }
        else {
            REPORT_MISSING("'('");
            ++errors;
        }
        errors += StmtPairBody();
        break;
    case 26:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 48:
        USING_RULE(r);
        token = lex->GetToken();
        errors += Stmt();
        break;
    case 27:
    case 41:
        USING_RULE(r);
        token = lex->GetToken();
        errors += Stmt();
        errors += Stmt();
        break;
    case 28:
    case 29:
    case 37:
    case 40:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
        USING_RULE(r);
        token = lex->GetToken();
        errors += StmtList();
        break;
    case 38:
    case 39:
        USING_RULE(r);
        token = lex->GetToken();
        errors += Stmt();
        errors += StmtList();
        break;
    case 49:
        USING_RULE(r);
        token = lex->GetToken();
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Action()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function:                                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::AnyOtherToken()
{
    int errors = 0;

    rule const r = checkRule(ntAnyOtherToken, token);
    USING_FUNCTION("AnyOtherToken");
    switch (r) {
    case 50:
        USING_RULE(r);
        token = lex->GetToken();
        errors += MoreTokens();
        if (token == RPAREN_T) {
            token = lex->GetToken();
        }
        else {
            REPORT_MISSING("')'");
            ++errors;
        }
        break;
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
    case 70:
    case 71:
    case 72:
    case 73:
    case 74:
    case 75:
    case 76:
    case 77:
    case 78:
    case 80:
    case 81:
        USING_RULE(r);
        token = lex->GetToken();
        break;
    case 79:
        USING_RULE(r);
        token = lex->GetToken();
        errors += AnyOtherToken();
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::AnyOtherToken()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}
