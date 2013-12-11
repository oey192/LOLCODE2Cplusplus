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
int yyerror(char *s);
int yylex(void);

%}

%union{
  int   num;
  char *str;
}

%type <int> expr
%type <str> include
%token TOKEN_NUMBER
%token TOKEN_WORD TOKEN_STRING
%token P_EXCL NEWLINE
%token A AND BIGR BYES CAN COMMENT DIAF GIMMEH GTFO HAI HAS
%token I IM IN ITZ IZ KTHX KTHXBYE LIEK LETTAR LINE LOL MAH
%token NERF NERFZ NOT NOWAI OR OUTTA OVAR OVARZ R
%token SMALR STDIN THAN TIEMZ TIEMZD UP UPZ VISIBLE
%token WORD XOR YARLY YR P_QMARK

%start program

%%

program : prog_start stmts prog_end { prog = $2; }
;

prog_start : HAI end_stmt
;

prog_end   : KTHXBYE
           | prog_end end_stmt
;

array : array_index array
      | TOKEN_WORD
;

array_index : TOKEN_NUMBER IN MAH
;

assignment : LOL l_value R r_value  { 
  if (typeid(*$4) == typeid(ASTNumber)) {
    std::cout << "number" << std::endl;
    (dynamic_cast<ASTSymbol&>(*$2)).val = ASTNumberSP(&dynamic_cast<ASTNumber&>(*$4));
  } else if (typeid(*$4) == typeid(ASTString)) {
    std::cout << "string" << std::endl;
    (dynamic_cast<ASTSymbol&>(*$2)).value = ASTStringSP(&dynamic_cast<ASTString&>(*$4));
  } else {
    std::cout << "4: nooooooooo" << std::endl;
    /*std::cout << typeid($4) << std::endl;
    std::cout << " num: " << std::endl;
    std::cout << typeid(ASTNumberSP) << std::endl;
    std::cout << " str: " << std::endl;
    std::cout << typeid(ASTStringSP) << std::endl;
    std::cout <<  " n: " << std::endl;
    std::cout <<  typeid(ASTNumber) << std::endl; 
    std::cout << " s: " << std:: endl;
    std::cout << typeid(ASTString) << std::endl;*/
  }
}
           | self_assignment
;

condexpr : expr BIGR THAN expr      { printf("[>]"); }
         | expr NOT BIGR THAN expr  { printf("[<=]"); }
         | expr SMALR THAN expr     { printf("[<=]"); }
         | expr NOT SMALR THAN expr { printf("[<=]"); }
         | expr LIEK expr           { printf("[<=]"); }
         | expr NOT LIEK expr       { printf("[<=]"); }
         | condexpr OR condexpr     { printf("[||]"); }
         | condexpr AND condexpr    { printf("[&&]"); }
         | condexpr XOR condexpr    { printf("[^^]"); }
         | NOT condexpr             { printf("[!]"); }
;

conditional : IZ condexpr then stmts KTHX
            | IZ condexpr then stmts elsethen stmts KTHX
;

declaration : I HAS A TOKEN_WORD initializer { $$ = $4;/* (dynamic_cast<ASTSymbol&>(*$$)).value = $5*/}
;

elsethen : NOWAI end_stmt
;

end_stmt : NEWLINE           { printf("\n"); }
;

exit : DIAF exit_status exit_message
     | BYES exit_status exit_message
;

exit_status : /* nothing */
            | TOKEN_NUMBER
            | TOKEN_WORD
;

exit_message : /* nothing */
             | TOKEN_STRING
             | TOKEN_WORD
;

expr : TOKEN_NUMBER          { $$ = $1; /*$$ = ASTNodeSP(new ASTNumber($1)); ? */ }
     | TOKEN_WORD            { $$ = $1; }
     | TOKEN_STRING          { $$ = $1; }
     | expr UP expr      { $$ = ASTNodeSP(new ASTSum($1, $3)); }
     | expr NERF expr    { $$ = ASTNodeSP(new ASTSub($1, $3)); }
     | expr TIEMZ expr   { $$ = ASTNodeSP(new ASTProduct($1, $3)); }
     | expr OVAR expr    { $$ = ASTNodeSP(new ASTDiv($1, $3)); }
;

include : CAN HAS TOKEN_WORD P_QMARK   { $$ = ASTNodeSP($3); }
        | CAN HAS TOKEN_STRING P_QMARK { $$ = ASTNodeSP($3); }

increment_expr : /* empty (defaults to 1) */
               | expr
;

initializer: ITZ r_value { $$ = $2; }
           | /* empty */ { $$ = ASTNodeSP(new ASTString(""));}
;

input_type : /* empty */
           | WORD
           | LINE
           | LETTAR
;

input_from : /* empty */
           | OUTTA TOKEN_WORD
           | OUTTA STDIN
;

input : GIMMEH input_type TOKEN_WORD input_from { $$ = ASTNodeSP(new ASTIn(ASTSymbolSP(&dynamic_cast<ASTSymbol&>(*$3)))); }
;

l_value : array
;

loop : IM IN YR TOKEN_WORD end_stmt stmts KTHX
;

output : VISIBLE expr { $$ = ASTNodeSP(new ASTOut(ASTExpressionSP(new ASTExpression($2)))); }
;

r_value : expr
;

self_assignment : UPZ TOKEN_WORD P_EXCL P_EXCL increment_expr
                | NERFZ TOKEN_WORD P_EXCL P_EXCL increment_expr
                | TIEMZD TOKEN_WORD P_EXCL P_EXCL increment_expr
                | OVARZ TOKEN_WORD P_EXCL P_EXCL increment_expr
;

stmt : include               { /*printf("Inclusion (%s)", $1);*/ }
     | declaration           { printf("Declaration"); }
     | loop                  { printf("Loop"); }
     | conditional           { printf("Conditional"); }
     | assignment            { printf("Assignment"); }
     | input                 { printf("Input"); }
     | output                { printf("Output"); }
     | expr                  { printf("Expression"); }
     | GTFO                  { printf("Break"); }
     | exit                  { printf("Exit"); }
     | COMMENT               { printf("/* COMMENT */"); }
;

stmts : /* no statements at all */  { printf("about to die1\n"); $$ = ASTNodeSP(new ASTStatements()); }
      | stmt end_stmt               { /*printf("about to if\n"); std::cout << *$$ << " " << *$1 << std::endl; if (!$$) {printf("in if\n"); $$ = ASTNodeSP(new ASTStatements()); } else { printf("Confused\n");} (dynamic_cast<ASTStatements&>(*$$)).statements.push_back($1);*/ }
      | stmts stmt end_stmt         { $$ = $1; printf("about to die3\n"); (dynamic_cast<ASTStatements&>(*$$)).statements.push_back($2); }
;

then : end_stmt
     | P_QMARK end_stmt
     | end_stmt YARLY
     | P_QMARK end_stmt YARLY
;

%%
int yyerror(string s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
}
int yyerror(char *s)
{
  return yyerror(string(s));
}
int main(int argc, char **argv)
{
  yyparse();
  if (prog) {
    TranslatorSP cpp = CreateCPPTranslator();
    cpp->translate("tmp/a.cpp", prog);
  }
  return 0;
} 