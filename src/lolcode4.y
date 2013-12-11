%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <typeinfo>
	#include <iostream>
	#include "ast.h"
	#include "translator.h"
	#define YYSTYPE ASTNodeSP
	ASTNodeSP prog;
	int yylex(void);
%}

%token EOL

%token WIN FAIL

%token HAI KTHXBYE VISIBLE GIMMEH VARIABLE_DECLARATION ITZ VARIABLE_ASSIGNMENT AN HAS_STDIO YR EXCLAMATION
%token OPERATOR_SUM OPERATOR_DIFF OPERATOR_PROD OPERATOR_DIV OPERATOR_MOD OPERATOR_MIN OPERATOR_MAX 
%token OPERATOR_SAME OPERATOR_NOTSAME OPERATOR_AND OPERATOR_OR OPERATOR_XOR OPERATOR_NOT
%token FOR_END FOR_START FOR_UPPIN FOR_NERFIN FOR_TIL FOR_WILE IF_START IF_YES IF_NOT IF_MAYBE
%token CONDITIONAL_END SWITCH_START SWITCH_CASE SWITCH_DEFAULT SWITCH_BREAK

%token String Number Variable

%start Program

%%
Program:
        ProgramStart
        ProgramBody
        ProgramEnd
        ;

ProgramStart:
          HAI Number EOL   	{ GEN_PROGRAM_START(); }
        | HAI EOL        	{ GEN_PROGRAM_START(); }
        ;

ProgramEnd:
          KTHXBYE EOL      	{ GEN_PROGRAM_END(); }
        | KTHXBYE        	{ GEN_PROGRAM_END(); }
        ;

ProgramBody:
        /* nothing */
        | ProgramBody EOL
        | ProgramBody Statement EOL
        ;

Statement:
        | ConsoleOutput
        | ConsoleInput
        | VariableDeclaration
        | VariableAssignment
        | HAS_STDIO
        | ForConstruct
        | IfStatement
        | SwitchStatement
        ;

StatementList:
        /* nothing */
        | StatementList Statement EOL
        ;

SwitchStatement:
        NumericalExpression EOL
        SWITCH_START EOL { GEN_SWITCH_START($1); }
                SwitchCases
        CONDITIONAL_END { GEN_COND_END(); }
        ;

SwitchStatementList:
        /* nothing */
        | SwitchStatementList Statement EOL
        | SwitchStatementList SWITCH_BREAK EOL { GEN_BREAK(); }
        ;

SwitchCases:
        /* nothing */
        | SwitchCases SWITCH_CASE String EOL { GEN_SWITCH_CASE_START($3); } SwitchStatementList { GEN_SWITCH_CASE_END(); }
        | SwitchCases SWITCH_DEFAULT EOL { GEN_SWITCH_CASE_DEFAULT_START(); } SwitchStatementList { GEN_SWITCH_CASE_END(); }
        ;

IfStatement:
        NumericalExpression EOL
        IF_START EOL
                IF_YES EOL { GEN_IF_START($1); } StatementList
                IfContents
        CONDITIONAL_END { GEN_COND_END(); }
        ;

IfContents:
        /* nothing */
        | IfContents IF_NOT EOL { GEN_IF_ELSE(); } StatementList
        | IfContents IF_MAYBE NumericalExpression { GEN_IF_ELSE_IF($3); } StatementList
        ;

ForConstruct:
        FOR_START Variable ForOperation YR Variable ForCondition EOL { GEN_FOR_START($5, $6, $3); }
                StatementList
        FOR_END Variable { GEN_FOR_END(); }
        ;

ForOperation: 
          FOR_UPPIN 	{ $$ = $1; } 
        | FOR_NERFIN 	{ $$ = $1; }
        ;

ForCondition:
          FOR_TIL Operation 		{ $$ = "!" + $2; }
        | FOR_WILE Operation 		{ $$ = $2; }
        ;

Expression:
          NumericalExpression
        | String
        ;

NumericalExpression:
          Operation
        | Number
        | Variable
        ;

Operation:
          OPERATOR_SUM NumericalExpression AN NumericalExpression 	{ $$ = GEN_OPERATOR("+",   $2, $4); }
        | OPERATOR_DIFF NumericalExpression AN NumericalExpression 	{ $$ = GEN_OPERATOR("-",   $2, $4); }
        | OPERATOR_PROD NumericalExpression AN NumericalExpression 	{ $$ = GEN_OPERATOR("*",   $2, $4); }
        | OPERATOR_DIV NumericalExpression AN NumericalExpression 	{ $$ = GEN_OPERATOR("/",   $2, $4); }
        | OPERATOR_MOD NumericalExpression AN NumericalExpression 	{ $$ = GEN_OPERATOR("%",   $2, $4); }
        | OPERATOR_SAME Expression AN Expression 					{ $$ = GEN_OPERATOR("==",  $2, $4); }
        | OPERATOR_NOTSAME Expression AN Expression 				{ $$ = GEN_OPERATOR("!=",  $2, $4); }
        | OPERATOR_AND NumericalExpression AN NumericalExpression 	{ $$ = GEN_OPERATOR("&&",  $2, $4); }
        | OPERATOR_OR NumericalExpression AN NumericalExpression 	{ $$ = GEN_OPERATOR("||",  $2, $4); }
        | OPERATOR_XOR NumericalExpression AN NumericalExpression 	{ $$ = GEN_OPERATOR("!=",  $2, $4); }
        | OPERATOR_NOT NumericalExpression 						{ $$ = GEN_OPERATOR("!",   "", $2); }
        | OPERATOR_MAX NumericalExpression AN NumericalExpression 	{ $$ = GEN_FUNCTION("max", $2, $4); }
        | OPERATOR_MIN NumericalExpression AN NumericalExpression 	{ $$ = GEN_FUNCTION("min", $2, $4); }
        ;

VariableAssignment:
          Variable VARIABLE_ASSIGNMENT NumericalExpression  { GEN_ASSIGN_VAR($1, $3, INT); }
        | Variable VARIABLE_ASSIGNMENT String 			{ GEN_ASSIGN_VAR($1, $3, STRING); }
        ;

VariableDeclaration:
          VARIABLE_DECLARATION Variable  				{ GEN_DECLARE_VAR($2, "", NONE); }
        | VARIABLE_DECLARATION Variable ITZ Number 		{ GEN_DECLARE_VAR($2, $4, INT); }
        | VARIABLE_DECLARATION Variable ITZ String 		{ GEN_DECLARE_VAR($2, $4, STRING); }
        ;

ConsoleInput:
        GIMMEH Variable { GEN_INPUT($2); }

ConsoleOutput:
          VISIBLE VisibleStatementArgs { GEN_PRINT("\"\\n\""); }
        | VISIBLE VisibleStatementArgs EXCLAMATION        
        ;

VisibleStatementArgs:
          NumericalExpression 					{ GEN_PRINT($1); }
        | String 								{ GEN_PRINT($1); }
        | VisibleStatementArgs NumericalExpression 	{ GEN_PRINT($2); }
        | VisibleStatementArgs String 				{ GEN_PRINT($2); }
        ;
%%
int yyerror(string s) {
	extern int yylineno;	// defined and maintained in lex.c
	extern char *yytext;	// defined and maintained in lex.c
	cerr << "ERROR: " << s << " at symbol \"" << yytext;
	cerr << "\" on line " << yylineno << endl;
	exit(1);
}
int yyerror(char *s) {
	return yyerror(string(s));
}
int main(int argc, char **argv) {
	yyparse();
	if (prog) {
		TranslatorSP cpp = CreateCPPTranslator();
		cpp->translate("tmp/a.cpp", prog);
	}
	return 0;
}