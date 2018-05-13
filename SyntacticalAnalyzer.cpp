/*******************************************************************************
* Assignment: Project 2 - Syntactic Analyzer for Scheme to C++ Translator      *
* Authors: Devin Brown & Ryan Moeller                                          *
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
    : lex(filename), gen(filename, &lex), token{lex.GetToken()}
{
    string name = filename;
    string p2name = name.substr(0, name.length()-3) + ".p2";
    p2file.open (p2name.c_str());

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
    p2file.close();
}


rule ruleOf(non_terminal nt, token_type token)
{
#include "firsts.hpp"

    if (token <= NONE or token >= MAX_TOKENS)
        return NoRule;

    return firsts[nt][token];
}

bool inFollows(non_terminal nt, token_type token)
{
#include "follows.hpp"

    if (token <= NONE or token >= MAX_TOKENS)
        return false;

    return follows[nt] & (1ULL << token);
}

void SyntacticalAnalyzer::Using_Rule(rule r)
{
    p2file << "Using Rule " << static_cast<int>(r) << endl;
}

void SyntacticalAnalyzer::Report_Missing(char const *expected)
{
    lex.ReportError("unexpected '" + lex.GetLexeme() + "' found; "
                    "expected " + expected);
}

void SyntacticalAnalyzer::Function_Entry(const char * funcName)
{
    p2file << "Entering " << funcName << " function; "
           << "current token is: " << lex.GetTokenName(token) << ", "
           << "lexeme: " << lex.GetLexeme() << endl;
}

void SyntacticalAnalyzer::Function_Exit(const char * funcName)
{
    p2file << "Exiting " << funcName << " function; "
           << "current token is: " << lex.GetTokenName(token) << endl;
}

rule SyntacticalAnalyzer::Seek_First_Or_Follow(const char * funcName,
                                               non_terminal nt,
                                               int& errors)
{
    rule r;

    while ((r = ruleOf(nt, token)) == NoRule
           and !inFollows(nt, token)
           and token != EOF_T) {
        lex.ReportError("unexpected '" + lex.GetLexeme() + "' "
                        "(" + lex.GetTokenName(token) + ") "
                        "found at beginning of " + funcName);
        ++errors;
        token = lex.GetToken();
    }

    return r;
}

void SyntacticalAnalyzer::Seek_Follow(const char * funcName,
                                      non_terminal nt,
                                      int& errors)
{
    while (!inFollows(nt, token)
           and token != EOF_T) {
        lex.ReportError("unexpected '" + lex.GetLexeme() + "' found at "
                        "end of " + funcName);
        ++errors;
        token = lex.GetToken();
    }
}


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

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntProgram, errors);

    if (r != NoRule) {
        Using_Rule(r);
        errors += Define();
        errors += More_Defines();
        if (token != EOF_T) {
            Report_Missing("end of file");
            ++errors;
        }
    }
    else {
        Report_Missing("a program"); // TODO: expected what?
        ++errors;
    }

    Seek_Follow(__func__, ntProgram, errors);

    Function_Exit(__func__);

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
    bool isMain = 0;

    Function_Entry(__func__);


    rule const r = Seek_First_Or_Follow(__func__, ntDefine, errors);

    if (r != NoRule) {
        Using_Rule(r);
        token = lex.GetToken();
    }
    else {
        Report_Missing("'('");
        ++errors;
    }

    if (token == DEFINE_T) {
        token = lex.GetToken();
    }
    else {
        Report_Missing("'define'");
        ++errors;
    }

    if (token == LPAREN_T) {
        token = lex.GetToken();
    }
    else {
        Report_Missing("'('");
        ++errors;
    }

    if (token == IDENT_T) {
        isMain = lex.GetLexeme() == "main";
        if ( isMain )
            gen.WriteCode(0, "int\n"); // Return type
        else
            gen.WriteCode(0, "Object\n"); // Return type
        gen.WriteCode(0, lex.GetLexeme()); // Function name
        token = lex.GetToken();
    }
    else {
        Report_Missing("an identifier");
        ++errors;
    }

    gen.WriteCode(0, "(\n");

    errors += Param_List();

    gen.WriteCode(0, " )\n");

    if (token == RPAREN_T) {
        token = lex.GetToken();
    }
    else {
        Report_Missing("')'");
        ++errors;
    }

    gen.WriteCode(0, "{\n");

    errors += Stmt();

    gen.WriteCode(0, ";\n");

    errors += Stmt_List(";\n");

    if (isMain)
        gen.WriteCode(0, ";\n\treturn 0");

    gen.WriteCode(0, ";\n}\n\n");

    if (token == RPAREN_T) {
        token = lex.GetToken();
    }
    else {
        Report_Missing("')'");
        ++errors;
    }

    Seek_Follow(__func__, ntDefine, errors);

    Function_Exit(__func__);

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

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntMore_Defines, errors);

    switch (r) {
    //Rule for: <more_defines> -> <define> <more_defines>
    case 3:
        Using_Rule(r);
        errors += Define();
        errors += More_Defines();
        break;
    //Rule for: <more_defines> -> lambda
    case 4:
        Using_Rule(r);
        break;
    case NoRule:
        Report_Missing("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::More_Defines()";
    }

    Seek_Follow(__func__, ntMore_Defines, errors);

    Function_Exit(__func__);

    return errors;
}

/*******************************************************************************
* Function: Stmt List                                                          *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number of errors                      *
* Description: This function will call stmt or can do nothing                  *
*******************************************************************************/
int SyntacticalAnalyzer::Stmt_List(std::string separator, bool tail)
{
    int errors = 0;

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntStmt_List, errors);

    switch (r) {
    //Rule for: <stmt_list> -> <stmt> <stmt_list>
    case 5:
        Using_Rule(r);
        if(tail)
            gen.WriteCode(0, separator);

        errors += Stmt();
        errors += Stmt_List(separator, true );
        break;
    //Rule for: <stmt_list> -> lambda
    case 6:
        Using_Rule(r);
        break;
    case NoRule:
        Report_Missing("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Stmt_List()";
    }

    Seek_Follow(__func__, ntStmt_List, errors);

    Function_Exit(__func__);

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

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntStmt, errors);

    switch (r) {
    //Rule for: <stmt> -> <literal>
    case 7:
        Using_Rule(r);
        errors += Literal();
        break;
    //Rule for: <stmt> -> IDENT_T
    case 8:
        Using_Rule(r);
        gen.WriteCode(0, lex.GetLexeme() );
        token = lex.GetToken();
        break;
    //Rule for: <stmt> -> LPAREN_T <action> RPAREN_T
    case 9:
        Using_Rule(r);
        token = lex.GetToken();
        errors += Action();
        if (token == RPAREN_T) {
            token = lex.GetToken();
        }
        else {
            Report_Missing("')'");
            ++errors;
        }
        break;
    case NoRule:
        Report_Missing("'('");
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Stmt()";
    }

    Seek_Follow(__func__, ntStmt, errors);

    Function_Exit(__func__);

    return errors;
}

/*******************************************************************************
* Function: Literal                                                            *
*                                                                              *
* Parameters: no parameters                                                    *
* Return value: integer representing the number of return values               *
* Description: This function will check for NUMLIT_T or STRLIT_T or            *
* QUOTE then call function quoted_lit                                          *
*******************************************************************************/
int SyntacticalAnalyzer::Literal()
{
    int errors = 0;

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntLiteral, errors);

    switch (r) {
    //Rule for: <literal> -> NUMLIT_T
    case 10:
    //Rule for: <literal> -> STRLIT_T
    case 11:
        Using_Rule(r);
        gen.WriteCode(0, "Object(" + lex.GetLexeme() + ")" );
        token = lex.GetToken();
        break;
    //Rule for: <literal> -> QUOTE_T <quoted_lit>
    case 12:
        Using_Rule(r);
        token = lex.GetToken();
        errors += Quoted_Lit();
        break;
    case NoRule:
        Report_Missing("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Literal()";
    }

    Seek_Follow(__func__, ntLiteral, errors);

    Function_Exit(__func__);

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

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntQuoted_Lit, errors);

    if (r != NoRule) {
        Using_Rule(r);
        errors += Any_Other_Token();
    }
    else {
        Report_Missing("something else"); // TODO: expected what?
        ++errors;
    }

    Seek_Follow(__func__, ntQuoted_Lit, errors);

    Function_Exit(__func__);

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

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntMore_Tokens, errors);

    switch (r) {
    //Rule for: <more_tokens> -> <any_other_token> <more_tokens>
    case 14:
        Using_Rule(r);
        errors += Any_Other_Token();
        errors += More_Tokens();
        break;
    //Rule for: <more_tokens> -> lambda
    case 15:
        Using_Rule(r);
        break;
    case NoRule:
        Report_Missing("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::More_Tokens()";
    }

    Seek_Follow(__func__, ntMore_Tokens, errors);

    Function_Exit(__func__);

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

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntParam_List, errors);

    switch (r) {
    //Rule for: <param_list> -> IDENT_T <param_list<
    case 16:
        Using_Rule(r);
        gen.WriteCode(1, "Object " + lex.GetLexeme() + ",\n");
        token = lex.GetToken();
        errors += Param_List();
        break;
    //Rule for: <param_list> -> lambda
    case 17:
        Using_Rule(r);
        gen.WriteCode(1, "...");
        break;
    case NoRule:
        Report_Missing("an identifier or ')'"); // TODO: verify expected
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Param_List()";
    }

    Seek_Follow(__func__, ntParam_List, errors);

    Function_Exit(__func__);

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

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntElse_Part, errors);

    switch (r) {
    //Rule for: <else_part> -> <stmt>
    case 18:
        Using_Rule(r);
        errors += Stmt();
        break;
    //Rule for: <else_part> -> lambda
    case 19:
        Using_Rule(r);
        break;
    case NoRule:
        Report_Missing("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Else_Part()";
    }

    Seek_Follow(__func__, ntElse_Part, errors);

    Function_Exit(__func__);

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

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntStmt_Pair, errors);

    switch (r) {
    //Rule for: <stmt_pair> -> LPAREN_T <stmt_pair_body>
    case 20:
        Using_Rule(r);
        token = lex.GetToken();
        errors += Stmt_Pair_Body();
        break;
    //Rule for: <stmt_pair> -> lambda
    case 21:
        Using_Rule(r);
        break;
    case NoRule:
        Report_Missing("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Stmt_Pair()";
    }

    Seek_Follow(__func__, ntStmt_Pair, errors);

    Function_Exit(__func__);

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

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntStmt_Pair_Body, errors);

    switch (r) {
    //Rule for: <stmt_pair_body> -> <stmt> <stmt> RPAREN_T <stmt_pair>
    case 22:
        Using_Rule(r);
        errors += Stmt();
        errors += Stmt();
        if (token == RPAREN_T) {
            token = lex.GetToken();
        }
        else {
            Report_Missing("')'");
            ++errors;
        }
        errors += Stmt_Pair();
        break;
    //Rule for: <stmt_pair_body> -> ELSE_T <stmt> RPAREN_T
    case 23:
        Using_Rule(r);
        token = lex.GetToken();
        errors += Stmt();
        if (token == RPAREN_T) {
            token = lex.GetToken();
        }
        else {
            Report_Missing("')'");
            ++errors;
        }
        break;
    case NoRule:
        Report_Missing("something else'"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Stmt_Pair_Body()";
    }

    Seek_Follow(__func__, ntStmt_Pair_Body, errors);

    Function_Exit(__func__);

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

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntAction, errors);

    switch (r) {
    //Rule for: <action> -> IF_T <stmt> <stmt> <else_part>
    case 24:
        Using_Rule(r);
        token = lex.GetToken();
        errors += Stmt();
        gen.WriteCode(0, " ? ");
        errors += Stmt();
        gen.WriteCode(0, " : ");
        errors += Else_Part();
        break;
    //Rule for: <action> -> COND_T LPAREN_T <stmt_pair_body>
    case 25:
        Using_Rule(r);
        token = lex.GetToken();
        if (token == LPAREN_T) {
            token = lex.GetToken();
        }
        else {
            Report_Missing("'('");
            ++errors;
        }
        errors += Stmt_Pair_Body();
        break;
    //Rule for: <action> -> LISTOP_T <stmt>
    case 26:
    //Rule for: <action> -> NOT_T <stmt>
    case 30:
    //Rule for: <action> -> NUMBERP_T <stmt>
    case 31:
    //Rule for: <action> -> SYMBOLP_T <stmt>
    case 32:
    //Rule for: <action> -> LISTP_T <stmt>
    case 33:
    //Rule for: <action> -> ZEROP_T <stmt>
    case 34:
    //Rule for: <action> -> NULLP_T <stmt>
    case 35:
    //Rule for: <action> -> STRINGP_T <stmt>
    case 36:
        Using_Rule(r);
        token = lex.GetToken();
        errors += Stmt();
        break;
    //Rule for: <action> -> DISPLAY_T <stmt>
    case 48:
        Using_Rule(r);
        gen.WriteCode(1, "cout << " );
        token = lex.GetToken();
        errors += Stmt();
        break;
    //Rule for: <action> -> CONS_T <stmt> <stmt>
    case 27:
    //Rule for: <action> -> MODULO_T <stmt> <stmt>
    case 41:
        Using_Rule(r);
        token = lex.GetToken();
        errors += Stmt();
        errors += Stmt();
        break;

    //Rule for: <action> -> PLUS_T <stmt_list>
    case 37:
        Using_Rule(r);
        token = lex.GetToken();
        errors += Stmt_List(" + ");
        break;
    //Rule for: <action> -> AND_T <stmt_list>
    case 28:
    //Rule for: <action> -> OR_T <stmt_list>
    case 29:
    //Rule for: <action> -> MULT_T <stmt_list>
    case 40:
    //Rule for: <action> -> EQUALTO_T <stmt_list>
    case 42:
    //Rule for: <action> -> GT_T <stmt_list>
    case 43:
    //Rule for: <action> -> LT_T <stmt_list>
    case 44:
    //Rule for: <action> -> GTE_T <stmt_list>
    case 45:
    //Rule for: <action> -> LTE_T <stmt_list>
    case 46:
    //Rule for: <action> -> IDENT_T <stmt_list>
    case 47:
        Using_Rule(r);
        token = lex.GetToken();
        errors += Stmt_List(", ");
        break;
    //Rule for: <action> -> MINUS_T <stmt> <stmt_list>
    case 38:
    //Rule for: <action> -> DIV_T <stmt> <stmt_list>
    case 39:
        Using_Rule(r);
        token = lex.GetToken();
        errors += Stmt();
        errors += Stmt_List(", ");
        break;
    //Rule for: <action> -> NEWLINE_T
    case 49:
        Using_Rule(r);
        gen.WriteCode(1, "cout << endl" );
        token = lex.GetToken();
        break;
    case NoRule:
        Report_Missing("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Action()";
    }

    Seek_Follow(__func__, ntAction, errors);

    Function_Exit(__func__);

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

    Function_Entry(__func__);

    rule const r = Seek_First_Or_Follow(__func__, ntAny_Other_Token, errors);

    switch (r) {
    //Rule for: <any_other_token> -> LPAREN_T <more_tokens> RPAREN_T
    case 50:
        Using_Rule(r);
        token = lex.GetToken();
        errors += More_Tokens();
        if (token == RPAREN_T) {
            token = lex.GetToken();
        }
        else {
            Report_Missing("')'");
            ++errors;
        }
        break;
    //Rule for: <any_other_token> -> IDENT_T
    case 51:
    //Rule for: <any_other_token> -> NUMLIT_T
    case 52:
    //Rule for: <any_other_token> -> STRLIT_T
    case 53:
    //Rule for: <any_other_token> -> CONS_T
    case 54:
    //Rule for: <any_other_token> -> IF_T
    case 55:
    //Rule for: <any_other_token> -> DISPLAY_T
    case 56:
    //Rule for: <any_other_token> -> NEWLINE_T
    case 57:
    //Rule for: <any_other_token> -> LISTOP_T
    case 58:
    //Rule for: <any_other_token> -> AND_T
    case 59:
    //Rule for: <any_other_token> -> OR_T
    case 60:
    //Rule for: <any_other_token> -> NOT_T
    case 61:
    //Rule for: <any_other_token> -> DEFINE_T
    case 62:
    //Rule for: <any_other_token> -> NUMBERP_T
    case 63:
    //Rule for: <any_other_token> -> SYMBOLP_T
    case 64:
    //Rule for: <any_other_token> -> LISTP_T
    case 65:
    //Rule for: <any_other_token> -> ZEROP_T
    case 66:
    //Rule for: <any_other_token> -> NULLP_T
    case 67:
    //Rule for: <any_other_token> -> STRINGP_T
    case 68:
    //Rule for: <any_other_token> -> PLUS_T
    case 69:
    //Rule for: <any_other_token> -> MINUS_T
    case 70:
    //Rule for: <any_other_token> -> DIV_T
    case 71:
    //Rule for: <any_other_token> -> MULT_T
    case 72:
    //Rule for: <any_other_token> -> MODULO_T
    case 73:
    //Rule for: <any_other_token> -> EQUALTO_T
    case 74:
    //Rule for: <any_other_token> -> GT_T
    case 75:
    //Rule for: <any_other_token> -> LT_T
    case 76:
    //Rule for: <any_other_token> -> GTE_T
    case 77:
    //Rule for: <any_other_token> -> LTE_T
    case 78:
    //Rule for: <any_other_token> -> COND_T
    case 80:
    //Rule for: <any_other_token> -> ELSE_T
    case 81:
        Using_Rule(r);
        token = lex.GetToken();
        break;
    //Rule for: <any_other_token> -> QUOTE_T <any_other_token>
    case 79:
        Using_Rule(r);
        token = lex.GetToken();
        errors += Any_Other_Token();
        break;
    case NoRule:
        Report_Missing("something else"); // TODO: expected what?
        ++errors;
        break;
    default:
        throw "unhandled rule in SyntacticalAnalyzer::Any_Other_Token()";
    }

    Seek_Follow(__func__, ntAny_Other_Token, errors);

    Function_Exit(__func__);

    return errors;
}
