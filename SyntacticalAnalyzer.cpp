/*******************************************************************************
* Assignment: Project 2 - Syntactic Analyzer for Scheme to C++ Translator      *
* Author: Devin Brown                                                          *
* Date: Spring 2018                                                            *
* File: SyntacticalAnalyzer.cpp                                                *
*                                                                              *
* Description: This file contains the functions necessary to                   *
* analyze the syntax for the language specificed in project 2                  *
*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>

#include "SyntacticalAnalyzer.h"

using namespace std;

/*******************************************************************************
* Function: Syntactical Analyzer                                               *
*                                                                              *
* Parameters: char * filename                                                  *
* Return value: no return value                                                * 
* Description: This function will open the file to be analyzed and load its    *
* contents into the lexical analyzer.                                          *
* It will also open the used to write the results of the syntacit analysis to  *
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
* Function: Syntactical Analyzer Destructor                                    *
*                                                                              *
* Parameters: takes no parameters                                              *
* Return value: no return value                                                *
* Description: This function will free up lex from memory and close            *
*  the .p2 results file                                                        *
*******************************************************************************/
SyntacticalAnalyzer::~SyntacticalAnalyzer()
{
    delete lex;
    p2file.close();
}


typedef char rule;
enum { NoRule = 0 };

enum non_terminal {
    ntProgram, ntDefine, ntMore_Defines, ntStmt_List, ntStmt, ntLiteral,
    ntQuoted_Lit, ntMore_Tokens, ntParam_List, ntElse_Part, ntStmt_Pair,
    ntStmt_Pair_Body, ntAction, ntAny_Other_Token
};

rule checkRule(non_terminal nt, token_type token)
{
#include "syntaxrules.hpp"

    if (token <= NONE || token >= MAX_TOKENS)
        return NoRule;

    return rules[nt][token];
}

#define USING_RULE(rule)                                                \
    do { p2file << "Using Rule " << static_cast<int>(rule) << endl; } while (0)
#define REPORT_MISSING(expected)                                        \
    do { lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; " \
                          "expected " + (expected)); } while (0)
#define FUNCTION_ENTRY(funcName)                                        \
    do { p2file << "Entering " << funcName << " function; current token is: " \
                << lex->GetTokenName(token) << ", lexeme: "             \
                << lex->GetLexeme() << endl; } while (0)
#define FUNCTION_EXIT(funcName)                                         \
    do { p2file << "Exiting " << funcName << " function; current token is: " \
                << lex->GetTokenName(token) << endl; } while (0)

/*******************************************************************************
* Function: Program                                                            *
*                                                                              *
* Parameters: takes no parameters                                              *
* Return value: returns an integer represent the number of erros               *
* Description: This function is called from the constructor and is the first   *
* check for valid syntax                                                       *
*******************************************************************************/
int SyntacticalAnalyzer::Program()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    // token should be in firsts of Program

    rule const r = checkRule(ntProgram, token);

    if (r != NoRule) {
        USING_RULE(r);
        errors += Define();
        errors += More_Defines();
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
* Function: Define                                                             *
*                                                                              *
* Parameters: takes no parameters                                              *
* Return value: integer representing the number of errors                      *
* Description: This function will expect to find ( and ) and will call         *
* functions Define Param_List Stmt Stmt_List                                   *
*******************************************************************************/
int SyntacticalAnalyzer::Define()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntDefine, token);

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

    errors += Param_List();

    if (token == RPAREN_T) {
        token = lex->GetToken();
    }
    else {
        REPORT_MISSING("')'");
        ++errors;
    }

    errors += Stmt();
    errors += Stmt_List();

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
* Function: More Defines                                                       *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number of errors                      *
* Description: This function will call defines or it can do nothing            *
*******************************************************************************/
int SyntacticalAnalyzer::More_Defines()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntMore_Defines, token);

    switch (r) {
    case 3:
        USING_RULE(r);
        errors += Define();
        errors += More_Defines();
        break;
    case 4:
        USING_RULE(r);
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::More_Defines()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function: Stmt List                                                          *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number of errors                      *
* Description: This function will call stmt or can do nothing                  *
*******************************************************************************/
int SyntacticalAnalyzer::Stmt_List()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntStmt_List, token);

    switch (r) {
    case 5:
        USING_RULE(r);
        errors += Stmt();
        errors += Stmt_List();
        break;
    case 6:
        USING_RULE(r);
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Stmt_List()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function: Stmt                                                               *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number errors                         *
* Description: This function will call literal or an IDENT_T or it will look   *
* for ( then call function action                                              *
*******************************************************************************/
int SyntacticalAnalyzer::Stmt()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntStmt, token);

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
* Function: Literal                                                            *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number of return values               *
* Description: This function will check for NUMLIT_T or STRLIT_T or                *
* QUOTE then call function quoted_lit                                          *
*******************************************************************************/
int SyntacticalAnalyzer::Literal()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntLiteral, token);

    switch (r) {
    case 10:
    case 11:
        USING_RULE(r);
        token = lex->GetToken();
        break;
    case 12:
        USING_RULE(r);
        token = lex->GetToken();
        errors += Quoted_Lit();
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
* Function: Quoted Lit                                                         *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number of errors                      *
* Description: This function will check for a token in the set                 *
* any other token                                                              *
*******************************************************************************/
int SyntacticalAnalyzer::Quoted_Lit()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntQuoted_Lit, token);

    if (r != NoRule) {
        USING_RULE(r);
        errors += Any_Other_Token();
    }
    else {
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function: More Tokens                                                        *
*                                                                              *
* Parameters: function takes no parameters                                     *
* Return value: integer representing the number of errors                      *
* Description: This function will check for any_other_token then call itself   * 
* or it can do nothing                                                         *
*******************************************************************************/
int SyntacticalAnalyzer::More_Tokens()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntMore_Tokens, token);

    switch (r) {
    case 14:
        USING_RULE(r);
        errors += Any_Other_Token();
        errors += More_Tokens();
        break;
    case 15:
        USING_RULE(r);
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::More_Tokens()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function: Param List                                                         *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number of errors                      *
* Description: This function will check for IDENT_T then call itself           *
* or it will do nothing                                                        *                
*******************************************************************************/
int SyntacticalAnalyzer::Param_List()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntParam_List, token);

    switch (r) {
    case 16:
        USING_RULE(r);
        token = lex->GetToken();
        errors += Param_List();
        break;
    case 17:
        USING_RULE(r);
        break;
    case NoRule:
        REPORT_MISSING("an identifier or ')'"); // TODO: verify expected
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Param_List()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function: Else Part                                                          *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number of errors                      *
* Description: This function will call stmt or do nothing                      *
*******************************************************************************/
int SyntacticalAnalyzer::Else_Part()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntElse_Part, token);

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
        throw "unhandled rule in SyntacticalAnalyzer::Else_Part()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function: Stmt Pair                                                          *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number of errors                      *
* Description: This function will check for ( then call stmt_pair_body         *
* or do nothing                                                                *
*******************************************************************************/
int SyntacticalAnalyzer::Stmt_Pair()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntStmt_Pair, token);

    switch (r) {
    case 20:
        USING_RULE(r);
        token = lex->GetToken();
        errors += Stmt_Pair_Body();
        break;
    case 21:
        USING_RULE(r);
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Stmt_Pair()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function: Stmt Pair Body                                                     *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number of errors                      *
* Description: This function will call stmt then stmt then check for )         *
* then call itself or check for ELSE_T then call stmt and check for )          *
*******************************************************************************/
int SyntacticalAnalyzer::Stmt_Pair_Body()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntStmt_Pair_Body, token);

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
        errors += Stmt_Pair();
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
        throw "unhandled rule in SyntacticalAnalyzer::Stmt_Pair_Body()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}

/*******************************************************************************
* Function: Action                                                             *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number of errors                      *
* Description: This function will check for an operator then call either stmt  *
* or stmt_list or both in any order                                            *
*******************************************************************************/
int SyntacticalAnalyzer::Action()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntAction, token);

    switch (r) {
    case 24:
        USING_RULE(r);
        token = lex->GetToken();
        errors += Stmt();
        errors += Stmt();
        errors += Else_Part();
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
        errors += Stmt_Pair_Body();
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
        errors += Stmt_List();
        break;
    case 38:
    case 39:
        USING_RULE(r);
        token = lex->GetToken();
        errors += Stmt();
        errors += Stmt_List();
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
* Function: Any Other Token                                                    *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number of errors                      *
* Description: This function will check for a token in any_other_token set     *
* if token is LPAREN_T more tokens is call followed by a check for RPAREN_T    *
* if QUOTE_T is found the function calls itself                                *
*******************************************************************************/
int SyntacticalAnalyzer::Any_Other_Token()
{
    int errors = 0;

    FUNCTION_ENTRY(__FUNCTION__);

    rule const r = checkRule(ntAny_Other_Token, token);

    switch (r) {
    case 50:
        USING_RULE(r);
        token = lex->GetToken();
        errors += More_Tokens();
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
        errors += Any_Other_Token();
        break;
    case NoRule:
        REPORT_MISSING("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Any_Other_Token()";
    }

    FUNCTION_EXIT(__FUNCTION__);

    return errors;
}
