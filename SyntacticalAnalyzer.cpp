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

/*******************************************************************************
 * Function:                                                                    *
 *                                                                              *
 * Parameters:                                                                  *
 * Return value:                                                                *
 * Description: This function will                                              *
 *******************************************************************************/
int SyntacticalAnalyzer::Program()
{
	p2file << "Entering Program function; current token is: "
					<< lex->GetTokenName(token) << endl;
	int errors = 0;
	// token should be in firsts of Program
	// Body of function goes here.
	p2file << "Using Rule 1" << endl;
	//errors += Define();
	//errors += More_Defines();
	if (token != EOF_T)
	{
		errors++;
		lex->ReportError("Missing end of file at end of program");
	}
	// token should be in follows of Program
	p2file << "Exiting Program function; current token is: "
					<< lex->GetTokenName(token) << endl;
	return errors;
}

typedef unsigned rule;
enum { NoRule = 0 };

enum non_terminal {
    ntProgram, ntDefine, ntMoreDefines, ntStmtList, ntStmt, ntLiteral,
    ntQuotedLit, ntMoreTokens, ntParamList, ntElsePart, ntStmtPair,
    ntStmtPairBody, ntAction, ntAnyOtherToken
};

static rule const rules[][MAX_TOKENS] = {
    // Rows are non-terminals, columns are tokens
};

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

    rule r = rules[ntDefine][token];

    if (r != NoRule) {
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
    }
    else {
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected '('");
        ++errors;
    }

    if (token == DEFINE_T) {
        token = lex->GetToken();
    }
    else {
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected 'define'");
        ++errors;
    }

    if (token == LPAREN_T) {
        token = lex->GetToken();
    }
    else {
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected '('");
        ++errors;
    }

    if (token == IDENT_T) {
        token = lex->GetToken();
    }
    else {
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected an identifier");
        ++errors;
    }

    errors += ParamList();

    if (token == RPAREN_T) {
        token = lex->GetToken();
    }
    else {
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected ')'");
        ++errors;
    }

    errors += Stmt();
    errors += StmtList();

    if (token == RPAREN_T) {
        token = lex->GetToken();
    }
    else {
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected ')'");
        ++errors;
    }

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

    rule r = rules[ntMoreDefines][token];

    switch (r) {
    case 3:
	p2file << "Using Rule " << r << endl;
        errors += Define();
        errors += MoreDefines();
        break;
    case 4:
	p2file << "Using Rule " << r << endl;
        break;
    case NoRule:
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::MoreDefines()";
    }

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

    rule r = rules[ntStmtList][token];

    switch (r) {
    case 5:
	p2file << "Using Rule " << r << endl;
        errors += Stmt();
        errors += StmtList();
        break;
    case 6:
	p2file << "Using Rule " << r << endl;
        break;
    case NoRule:
        lex->ReportError("TODO");
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::StmtList()";
    }

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

    rule r = rules[ntStmt][token];

    switch (r) {
    case 7:
	p2file << "Using Rule " << r << endl;
        errors += Literal();
        break;
    case 8:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        break;
    case 9:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        errors += Action();
        if (token == RPAREN_T) {
            token = lex->GetToken();
        }
        else {
            lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                             "expected ')'");
            ++errors;
        }
        break;
    case NoRule:
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected ')'");
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Stmt()";
    }

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

    rule r = rules[ntLiteral][token];

    switch (r) {
    case 10:
    case 11:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        break;
    case 12:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        errors += QuotedLit();
        break;
    case NoRule:
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Literal()";
    }

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

    rule r = rules[ntQuotedLit][token];

    if (r != NoRule) {
	p2file << "Using Rule " << r << endl;
        errors += AnyOtherToken();
    }
    else {
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected something else"); // TODO: expected what?
        ++errors;
    }

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

    rule r = rules[ntMoreTokens][token];

    switch (r) {
    case 14:
	p2file << "Using Rule " << r << endl;
        errors += AnyOtherToken();
        errors += MoreTokens();
        break;
    case 15:
	p2file << "Using Rule " << r << endl;
        break;
    case NoRule:
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::MoreTokens()";
    }

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

    rule r = rules[ntParamList][token];

    switch (r) {
    case 16:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        errors += ParamList();
        break;
    case 17:
	p2file << "Using Rule " << r << endl;
        break;
    case NoRule:
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected an identifier or ')'"); // TODO: verify expected
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::ParamList()";
    }

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

    rule r = rules[ntElsePart][token];

    switch (r) {
    case 18:
	p2file << "Using Rule " << r << endl;
        errors += Stmt();
        break;
    case 19:
	p2file << "Using Rule " << r << endl;
        break;
    case NoRule:
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::ElsePart()";
    }

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

    rule r = rules[ntStmtPair][token];

    switch (r) {
    case 20:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        errors += StmtPairBody();
        break;
    case 21:
	p2file << "Using Rule " << r << endl;
        break;
    case NoRule:
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::StmtPair()";
    }

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

    rule r = rules[ntStmtPairBody][token];

    switch (r) {
    case 22:
	p2file << "Using Rule " << r << endl;
        errors += Stmt();
        errors += Stmt();
        if (token == RPAREN_T) {
            token = lex->GetToken();
        }
        else {
            lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                             "expected ')'");
            ++errors;
        }
        errors += StmtPair();
        break;
    case 23:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        errors += Stmt();
        if (token == RPAREN_T) {
            token = lex->GetToken();
        }
        else {
            lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                             "expected ')'");
            ++errors;
        }
        break;
    case NoRule:
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected something else'"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::StmtPairBody()";
    }

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

    rule r = rules[ntAction][token];

    switch (r) {
    case 24:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        errors += Stmt();
        errors += Stmt();
        errors += ElsePart();
        break;
    case 25:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        if (token == LPAREN_T) {
            token = lex->GetToken();
        }
        else {
            lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                             "expected '('");
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
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        errors += Stmt();
        break;
    case 27:
    case 41:
	p2file << "Using Rule " << r << endl;
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
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        errors += StmtList();
        break;
    case 38:
    case 39:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        errors += Stmt();
        errors += StmtList();
        break;
    case 49:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        break;
    case NoRule:
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Action()";
    }

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

    rule r = rules[ntAnyOtherToken][token];

    switch (r) {
    case 50:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        errors += MoreTokens();
        if (token == RPAREN_T) {
            token = lex->GetToken();
        }
        else {
            lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                             "expected ')'");
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
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        break;
    case 79:
	p2file << "Using Rule " << r << endl;
        token = lex->GetToken();
        errors += AnyOtherToken();
        break;
    case NoRule:
        lex->ReportError("unexpected '" + lex->GetLexeme() + "' found; "
                         "expected something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::AnyOtherToken()";
    }

    return errors;
}
