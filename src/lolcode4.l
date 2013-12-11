%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "ast.h"
	#define YYSTYPE ASTNodeSP
	#include "lolcode.tab.hpp"
%}


OBTW(.|\r|\n)*TLDR\r?\n {}
BTW[^\r\n]*\r?\n 	{ return COMMENT; }
"HAI"			{ return HAI; }
"KTHXBYE"			{ return KTHXBYE; }
"VISIBLE"			{ return VISIBLE; }
"GIMMEH"			{ return GIMMEH; }
"I HAS A"			{ return VAR_DECLARATION; }
"ITZ"			{ return ITZ; }
"R"				{ return VAR_ASSIGNMENT; }
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
"UPPIN"			{ sscanf(yytext, "%d", &yylval->value); return UPPIN }
"NERFIN"			{ sscanf(yytext, "%d", &yylval->value); return NERFIN }
"TIL"			{ sscanf(yytext, "%d", &yylval->value); return TIL }
"WILE"			{ sscanf(yytext, "%d", &yylval->value); return WHILE }
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

[a-zA-Z][a-zA-Z0-9_]* 		{ sscanf(yytext, "%d", &yylval->value); return Variable; }
('-'|'+')?[0-9]+(.[0-9]+)? 	{ sscanf(yytext, "%d", &yylval->value); return Number }
\"[^\r\n\"]*\"        		{ sscanf(yytext, "%d", &yylval->value); return String }
!                             { SAVE_STRING_AND_TOKEN(EXCLAMATION); }
\r?\n                         { return EOL; }
,                             { return EOL; }
[ \t]                         ;