%{
	#define YYSTYPE ASTNodeSP
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
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
        ProgramEnd
        ;

ProgramStart:
          HAI NUMBER EOL   	{ printf("Program Start"); }
        | HAI EOL        	{ printf("Program Start"); }
        ;

ProgramEnd:
          KTHXBYE EOL      	{ printf("Program End"); }
        | KTHXBYE        	{ printf("Program End"); }
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
                IF_YES EOL { cout << "If Start " << *$1 << endl; } StatementList
                IfContents
        CONDITIONAL_END { cout << "Conditional End " << endl; }
        ;

IfContents:
        /* nothing */
        | IfContents IF_NOT EOL { cout << "If Else" << endl;} StatementList
        | IfContents IF_MAYBE NumericalExpression { cout << "If ElseIf " << *$3 << endl; } StatementList
        ;

ForConstruct:
        FOR_START VARIABLE ForOperation YR VARIABLE ForCondition EOL { cout << "For Loop Start " << *$5 <<" "<< *$6<<" " << *$3 << endl; }
                StatementList
        FOR_END VARIABLE { cout << "For Loop End" << endl; }
        ;

ForOperation: 
          FOR_UPPIN 	{ $$ = $1; } 
        | FOR_NERFIN 	{ $$ = $1; }
        ;

ForCondition:
          FOR_TIL Operation 		{  }
        | FOR_WILE Operation 		{  }
        ;

Expression:
          NumericalExpression
        | STRING
        ;

NumericalExpression:
          Operation
        | NUMBER
        | VARIABLE
        ;
        
StringExpression:
		StringOperation
	   | STRING
	   | VARIABLE
	   ;

Operation:
          OPERATOR_SUM NumericalExpression AN NumericalExpression 	{ cout << *$2 << "Operator + " << *$4 << endl; }
        | OPERATOR_DIFF NumericalExpression AN NumericalExpression 	{ cout << *$2 << "Operator - " << *$4 << endl; }
        | OPERATOR_PROD NumericalExpression AN NumericalExpression 	{ cout << *$2 << "Operator * " << *$4 << endl; }
        | OPERATOR_DIV NumericalExpression AN NumericalExpression 	{ cout << *$2 << "Operator / " << *$4 << endl; }
        | OPERATOR_MOD NumericalExpression AN NumericalExpression 	{ cout << *$2 << "Operator % " << *$4 << endl; }
        | OPERATOR_SAME Expression AN Expression 					{ cout << *$2 << "Operator == " << *$4 << endl; }
        | OPERATOR_NOTSAME Expression AN Expression 				{ cout << *$2 << "Operator != " << *$4 << endl; }
        | OPERATOR_AND NumericalExpression AN NumericalExpression 	{ cout << *$2 << "Operator && " << *$4 << endl; }
        | OPERATOR_OR NumericalExpression AN NumericalExpression 	{ cout << *$2 << "Operator || " << *$4 << endl; }
        | OPERATOR_XOR NumericalExpression AN NumericalExpression 	{ cout << *$2 << "Operator != " << *$4 << endl; }
        | OPERATOR_NOT NumericalExpression 						{ cout << "Operator ! " << *$2 << endl; }
        | OPERATOR_MAX NumericalExpression AN NumericalExpression 	{ cout << *$2 << "Operator max " << *$4 << endl; }
        | OPERATOR_MIN NumericalExpression AN NumericalExpression 	{ cout << *$2 << "Operator min " << *$4 << endl; }
        ;
        
StringOperation:
	 	OPERATOR_CONCAT StringExpression AN StringExpression		{ cout << *$2 << " Smoosh " << *$4 << endl; }
	   ;

VariableAssignment:
          VARIABLE VARIABLE_ASSIGNMENT NumericalExpression  { cout << "Variable Assignment " << *$1 << *$3 << "Int" << endl; }
        | VARIABLE VARIABLE_ASSIGNMENT StringExpression 	{ cout << "Variable Assignment " << *$1 << *$3 << "String" << endl; }
        ;

VariableDeclaration:
          VARIABLE_DECLARATION VARIABLE  				{ cout << "Variable Declaration " << *$2 << "None" << endl; }
        | VARIABLE_DECLARATION VARIABLE ITZ NUMBER 		{ cout << "Variable Declaration " << *$2 << *$4 << "Int" << endl; }
        | VARIABLE_DECLARATION VARIABLE ITZ STRING 		{ cout << "Variable Declaration " << *$2 << *$4 << "String" << endl; }
        ;

ConsoleInput:
        GIMMEH VARIABLE { cout << "Input " << *$2 << endl; }

ConsoleOutput:
          VISIBLE VisibleStatementArgs { cout << "OUTPUT: " << *$2 << endl; }
        | VISIBLE VisibleStatementArgs EXCLAMATION        
        ;

VisibleStatementArgs:
          NumericalExpression 					{ cout << "Print " << *$1 << endl; }
        | STRING 								{ cout << "Print " << *$1 << endl; }
        | VisibleStatementArgs NumericalExpression 	{ cout << "Print " << *$2 << endl; }
        | VisibleStatementArgs STRING 				{ cout << "Print " << *$2 << endl; }
        ;
%%

int main(int argc, char **argv) {
	yyparse();
	/*if (Program) {
		TranslatorSP cpp = CreateCPPTranslator();
		cpp->translate("tmp/a.cpp", Program);
	}*/
	return 0;
}