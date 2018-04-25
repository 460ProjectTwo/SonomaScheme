/*******************************************************************************
* Assignment: Project 2 - Syntactic Analyzer for Scheme to C++ Translator      *
* Author:                                                                      *
* Date: Spring 2018                                                            *
* File: SyntacticalAnalyzer.h                                                  *
*                                                                              *
* Description: This file contains the                                          *
*******************************************************************************/

#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

typedef char rule;
enum { NoRule = 0 };

enum non_terminal {
    ntProgram, ntDefine, ntMore_Defines, ntStmt_List, ntStmt, ntLiteral,
    ntQuoted_Lit, ntMore_Tokens, ntParam_List, ntElse_Part, ntStmt_Pair,
    ntStmt_Pair_Body, ntAction, ntAny_Other_Token
};

class SyntacticalAnalyzer
{
 public:
    SyntacticalAnalyzer(char * filename);
    ~SyntacticalAnalyzer();
 private:
    LexicalAnalyzer *lex;
    ofstream p2file;
    token_type token;

    int Program();
    int Define();
    int More_Defines();
    int Stmt_List();
    int Stmt();
    int Literal();
    int Quoted_Lit();
    int More_Tokens();
    int Param_List();
    int Else_Part();
    int Stmt_Pair();
    int Stmt_Pair_Body();
    int Action();
    int Any_Other_Token();

    void Using_Rule(rule);
    void Report_Missing(char const *);
    void Function_Entry(char const *);
    void Function_Exit(char const *);
    rule Seek_First_Or_Follow(char const *, non_terminal, int&);
    void Seek_Follow(char const *, non_terminal, int&);
};

#endif
