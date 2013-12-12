%{
	#define YYSTYPE ASTNodeSP
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "ast.h"
	#include "lolcode.tab.hpp"
%}

%%
OBTW(.|\r|\n)*TLDR\r?\n {}
BTW[^\r\n]*\r?\n 	{ return COMMENT; }
"HAI"			{ return HAI; }
"KTHXBYE"			{ return KTHXBYE; }
"VISIBLE"			{ return VISIBLE; }
"GIMMEH"			{ return GIMMEH; }
"I HAS A"			{ return VARIABLE_DECLARATION; }
"ITZ"			{ return ITZ; }
"R"				{ return VARIABLE_ASSIGNMENT; }
"SUM OF"			{ return OPERATOR_SUM; }
"DIFF OF"			{ return OPERATOR_DIFF; }
"PRODUKT OF"		{ return OPERATOR_PROD; }
"QUOSHUNT OF"		{ return OPERATOR_DIV; }
"MOD OF"			{ return OPERATOR_MOD; }
"BIGGR OF"		{ return OPERATOR_MAX; }
"SMALLR OF"		{ return OPERATOR_MIN; }
"BOTH SAEM"		{ return OPERATOR_SAME; }
"DIFFRNT"			{ return OPERATOR_NOTSAME; }
"AN"				{ return AN; }
"CAN HAS STDIO?"	{ return HAS_STDIO; }
"IM OUTTA YR"		{ return FOR_END; }
"IM IN YR"		{ return FOR_START; }
"YR"				{ return YR; }
"UPPIN"			{ return FOR_UPPIN; }
"NERFIN"			{ return FOR_NERFIN; }
"TIL"			{ return FOR_TIL; }
"WILE"			{ return FOR_WILE; }
"WIN"			{ return WIN; }
"FAIL"			{ return FAIL; }
"BOTH OF"			{ return OPERATOR_AND; }
"EITHER OF"		{ return OPERATOR_OR; }
"WON OF"			{ return OPERATOR_XOR; }
"NOT"			{ return OPERATOR_NOT; }
"O RLY?"			{ return IF_START; }
"YA RLY"			{ return IF_YES; }
"NO WAI"			{ return IF_NOT; }
"MEBBE"			{ return IF_MAYBE; }
"WTF?"			{ return SWITCH_START; }
"OMG"			{ return SWITCH_CASE; }
"OMGWTF"			{ return SWITCH_DEFAULT; }
"GTFO"			{ return SWITCH_BREAK; }
"OIC"			{ return CONDITIONAL_END; }
"SMOOSH"			{ return OPERATOR_CONCAT; }

[a-zA-Z][a-zA-Z0-9_]* 		{ yylval = ASTNodeSP(new ASTVariable(yytext)); return VARIABLE; }
('-'|'+')?[0-9]+(.[0-9]+)? 	{ yylval = ASTNodeSP(new ASTNumber(atof(yytext))); return NUMBER; }
\"[^\r\n\"]*\"        		{ yylval = ASTNodeSP(new ASTString(yytext)); return STRING; }
!                             { return EXCLAMATION; }
\r?\n                         { return EOL; }
,                             { return EOL; }
[ \t]                         ;
%%