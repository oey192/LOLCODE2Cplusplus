%{
	#define YYSTYPE ASTNodeSP
	#include <stdio.h>
	#include <stdlib.h>
	#include <string>
	#include <typeinfo>
	#include <iostream>
	#include "ast.h"
	#include "translator.h"
	int yylex(void);
	using namespace std;
	
int yyerror(string s) {
	extern int yylineno;
	extern char *yytext;
	cerr << "ERROR: " << s << " at symbol \"" << yytext;
	cerr << "\" on line " << yylineno << endl;
	exit(1);
}
int yyerror(char *s) {
	return yyerror(string(s));
}

ASTNodeSP prog;
%}


%token EOL

%token WIN FAIL

%token HAI KTHXBYE VISIBLE GIMMEH VARIABLE_DECLARATION ITZ VARIABLE_ASSIGNMENT AN HAS_STDIO YR EXCLAMATION
%token OPERATOR_SUM OPERATOR_DIFF OPERATOR_PROD OPERATOR_DIV OPERATOR_MOD OPERATOR_MIN OPERATOR_MAX
%token OPERATOR_SAME OPERATOR_NOTSAME OPERATOR_AND OPERATOR_OR OPERATOR_XOR OPERATOR_NOT COMMENT
%token FOR_END FOR_START FOR_UPPIN FOR_NERFIN FOR_TIL FOR_WILE IF_START IF_YES IF_NOT IF_MAYBE
%token CONDITIONAL_END SWITCH_START SWITCH_CASE SWITCH_DEFAULT SWITCH_BREAK OPERATOR_CONCAT

%token STRING NUMBER VARIABLE

%start Program

%%
Program:
        ProgramStart
        ProgramBody
        ProgramEnd          { prog = $2; }
        ;

ProgramStart:
          HAI NUMBER EOL   	
        | HAI EOL        	
        ;

ProgramEnd:
          KTHXBYE EOL      	
        | KTHXBYE        	
        ;

ProgramBody:
        /* nothing */                   { $$ = ASTNodeSP(new ASTStatements()); }
        | ProgramBody EOL               { (dynamic_cast<ASTStatements&>(*$$)).statements.push_back($1); }
        | ProgramBody Statement EOL     { (dynamic_cast<ASTStatements&>(*$1)).statements.push_back($2); $$ = $1;}
        ;

Statement:
        | ConsoleOutput
        | ConsoleInput
        | VariableDeclaration
        | VariableAssignment
        | HAS_STDIO             { $$ = ASTNodeSP(new ASTSTDIO()); }
        | ForConstruct
        | IfStatement
        | SwitchStatement
        ;

StatementList:
        /* nothing */   { $$ = ASTNodeSP(new ASTStatements()); }
        | StatementList Statement EOL { (dynamic_cast<ASTStatements&>(*$1)).statements.push_back($2); }
        ;

SwitchStatement:
        NumericalExpression EOL
        SWITCH_START EOL { cout << "Switch Start " << *$1 << endl; }
                SwitchCases
        CONDITIONAL_END { cout << "CONDITIONAL END " << endl; }
        ;

SwitchStatementList:
        /* nothing */
        | SwitchStatementList Statement EOL
        | SwitchStatementList SWITCH_BREAK EOL { cout << "BREAK" << endl; }
        ;

SwitchCases:
        /* nothing */
        | SwitchCases SWITCH_CASE STRING EOL { cout << "Switch Case Start " << *$3 << endl; } 
          SwitchStatementList { cout << "Switch Case End " << endl; }
        | SwitchCases SWITCH_DEFAULT EOL { cout << "Switch Case Default Start " << endl; } 
          SwitchStatementList { cout << "Switch Case End " << endl; }
        ;

IfStatement:
        NumericalExpression EOL
        IF_START EOL
                IF_YES EOL StatementList
                IfContents
        CONDITIONAL_END                     { (dynamic_cast<ASTIf&>(*$8)).clauses.push_front(make_pair($1, dynamic_pointer_cast<ASTStatements>($7))); $$ = $8; }
        ;

IfContents:
        /* nothing */                               { $$ = ASTNodeSP(new ASTIf()); }
        | IfContents IF_NOT EOL StatementList { (dynamic_cast<ASTIf&>(*$1)).clauses.push_back(make_pair(ASTNodeSP(new ASTTrue()), dynamic_pointer_cast<ASTStatements>($4))); $$ = $1; }
        | IfContents IF_MAYBE NumericalExpression StatementList { (dynamic_cast<ASTIf&>(*$1)).clauses.push_back(make_pair($3, dynamic_pointer_cast<ASTStatements>($4))); $$ = $1; }
        ;

ForConstruct:
        FOR_START VARIABLE ForOperation YR VARIABLE ForCondition EOL
                StatementList
        FOR_END VARIABLE            { $$ = ASTNodeSP(new ASTLoop(dynamic_pointer_cast<ASTPlusEquals>($3), dynamic_pointer_cast<ASTVariable>($5), $6, dynamic_pointer_cast<ASTStatements>($8))); }
        ;

ForOperation: 
          FOR_UPPIN 	{ $$ = ASTNodeSP(new ASTPlusEquals(1)); } 
        | FOR_NERFIN 	{ $$ = ASTNodeSP(new ASTPlusEquals(-1)); }
        ;

ForCondition:
          FOR_TIL Operation 		{ $$ = ASTNodeSP(new ASTNot($2)); }
        | FOR_WILE Operation 		{ $$ = $2; }
        ;

Expression:                 //done?
          NumericalExpression
        | StringOperation
        | STRING
        ;

NumericalExpression:        //done
          Operation
        | NUMBER
        | VARIABLE
        ;
        
StringExpression:           //done
		StringOperation
	   | STRING
	   | VARIABLE
	   ;

Operation:
          OPERATOR_SUM NumericalExpression AN NumericalExpression 	{ $$ = ASTNodeSP(new ASTSum($2, $4)); }
        | OPERATOR_DIFF NumericalExpression AN NumericalExpression 	{ $$ = ASTNodeSP(new ASTSub($2, $4)); }
        | OPERATOR_PROD NumericalExpression AN NumericalExpression 	{ $$ = ASTNodeSP(new ASTProduct($2, $4)); }
        | OPERATOR_DIV NumericalExpression AN NumericalExpression 	{ $$ = ASTNodeSP(new ASTDiv($2, $4)); }
        | OPERATOR_MOD NumericalExpression AN NumericalExpression 	{ $$ = ASTNodeSP(new ASTMod($2, $4)); }
        | OPERATOR_SAME Expression AN Expression 					{ $$ = ASTNodeSP(new ASTEq($2, $4)); }
        | OPERATOR_NOTSAME Expression AN Expression 				{ $$ = ASTNodeSP(new ASTNeq($2, $4)); }
        | OPERATOR_AND NumericalExpression AN NumericalExpression 	{ $$ = ASTNodeSP(new ASTAnd($2, $4)); }
        | OPERATOR_OR NumericalExpression AN NumericalExpression 	{ $$ = ASTNodeSP(new ASTOr($2, $4)); }
        | OPERATOR_XOR NumericalExpression AN NumericalExpression 	{ $$ = ASTNodeSP(new ASTXor($2, $4)); }
        | OPERATOR_NOT NumericalExpression 						    { $$ = ASTNodeSP(new ASTNot($2)); }
        | OPERATOR_MAX NumericalExpression AN NumericalExpression 	{ $$ = ASTNodeSP(new ASTMax($2, $4)); }
        | OPERATOR_MIN NumericalExpression AN NumericalExpression 	{ $$ = ASTNodeSP(new ASTMin($2, $4)); }
        ;
        
StringOperation:
	 	OPERATOR_CONCAT Expression AN Expression		           { $$ = ASTNodeSP(new ASTSmoosh($2, $4)); }
	   ;

VariableAssignment: /* May want to make this VAIRALBE VARIABLE_ASSIGNMENT Expression */
          VARIABLE VARIABLE_ASSIGNMENT NumericalExpression  { $$ = ASTNodeSP(new ASTVarAssignment(dynamic_pointer_cast<ASTVariable>($1), $3)); }
        | VARIABLE VARIABLE_ASSIGNMENT StringExpression 	{ $$ = ASTNodeSP(new ASTVarAssignment(dynamic_pointer_cast<ASTVariable>($1), $3)); }
        ;

VariableDeclaration:
          VARIABLE_DECLARATION VARIABLE  				{ $$ = ASTNodeSP(new ASTVarDeclaration(dynamic_pointer_cast<ASTVariable>($2))); }
        | VARIABLE_DECLARATION VARIABLE ITZ NUMBER 		{ $$ = ASTNodeSP(new ASTVarDeclaration(dynamic_pointer_cast<ASTVariable>($2), $4)); /*might want to make NUMBER NumericalExpression*/}
        | VARIABLE_DECLARATION VARIABLE ITZ STRING 		{ $$ = ASTNodeSP(new ASTVarDeclaration(dynamic_pointer_cast<ASTVariable>($2), $4)); /*might want to make STRING StringExpression */}
        ;

ConsoleInput:
        GIMMEH VARIABLE { $$ = ASTNodeSP(new ASTIn(dynamic_pointer_cast<ASTVariable>($2))); }

ConsoleOutput:
          VISIBLE VisibleStatementArgs              { $$ = ASTNodeSP(new ASTOut(dynamic_pointer_cast<ASTExpressions>($2), true)); }
        | VISIBLE VisibleStatementArgs EXCLAMATION  { $$ = ASTNodeSP(new ASTOut(dynamic_pointer_cast<ASTExpressions>($2), false)); }
        ;

VisibleStatementArgs:
          NumericalExpression 					     { $$ = ASTNodeSP(new ASTExpressions($1)); }
        | STRING 								     { $$ = ASTNodeSP(new ASTExpressions($1)); }
        | VisibleStatementArgs NumericalExpression 	 { (dynamic_cast<ASTExpressions&>(*$1)).expressions.push_back($2); }
        | VisibleStatementArgs STRING 				 { (dynamic_cast<ASTExpressions&>(*$1)).expressions.push_back($2); }
        ;
%%

int main(int argc, char *argv[]) {
	yyparse();
    string filename = argv[1];
	if (prog) {
		TranslatorSP cpp = CreateCPPTranslator();
		cpp->translate("tmp/" + filename + ".cpp", prog);
	}
	return 0;
}