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
        int MoreDefines();
        int StmtList();
        int Stmt();
        int Literal();
        int QuotedLit();
        int MoreTokens();
        int ParamList();
        int ElsePart();
        int StmtPair();
        int StmtPairBody();
        int Action();
        int AnyOtherToken();
};

#endif
