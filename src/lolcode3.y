%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *str) 
{
  fprintf(stderr,"error: %s\n",str);
} // Better error message
int yywrap() {return 1;}
int yylex(void);

%}

%union {
  int   num;
  char *str;
}

%token <num> T_NUMBER 
%token <str> T_WORD T_STRING
%token P_EXCL NEWLINE
%token A AND BIGR BYES CAN COMMENT DIAF GIMMEH GTFO HAI HAS 
%token I IM IN ITZ IZ KTHX KTHXBYE LIEK LETTAR LINE LOL MAH 
%token NERF NERFZ NOT NOWAI OR OUTTA OVAR OVARZ R 
%token SMALR STDIN THAN TIEMZ TIEMZD UP UPZ VISIBLE 
%token WORD XOR YARLY YR P_QMARK

%type <str> include

%expect 102

%start program

%%
program : prog_start stmts prog_end { printf("Valid program!\n"); }
;

array : array_index array
      | T_WORD
;

array_index : T_NUMBER IN MAH
;

assignment : LOL l_value R r_value  //     { /* printf("Assigning: %s = %s", $2, $4); */ }
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

declaration : I HAS A T_WORD initializer
;

elsethen : NOWAI end_stmt
;

end_stmt : NEWLINE           { printf("\n"); }
;

exit : DIAF exit_status exit_message
     | BYES exit_status exit_message
;

exit_status : /* nothing */
            | T_NUMBER
            | T_WORD
;

exit_message : /* nothing */
             | T_STRING
             | T_WORD
;

expr : T_NUMBER          { printf("[NUM:%d]", $1); }
     | T_WORD            { printf("[VAR:%s]", $1); }
     | T_STRING          { printf("[STR:%s]", $1); }
     | expr UP expr      { printf("[+]"); }
     | expr NERF expr    { printf("[-]"); }
     | expr TIEMZ expr   { printf("[*]"); }
     | expr OVAR expr    { printf("[/]"); }
;

include : CAN HAS T_WORD P_QMARK   { $$ = $3; }
        | CAN HAS T_STRING P_QMARK { $$ = $3; }

increment_expr : /* empty (defaults to 1) */
               | expr
;

initializer: ITZ r_value
           | /* empty */
;

input_type : /* empty */
           | WORD
           | LINE
           | LETTAR
;

input_from : /* empty */
           | OUTTA T_WORD
           | OUTTA STDIN
;

input : GIMMEH input_type T_WORD input_from
;

l_value : array
;

loop : IM IN YR T_WORD end_stmt stmts KTHX
;

output : VISIBLE expr
;

prog_start : HAI end_stmt
;

prog_end   : KTHXBYE
           | prog_end end_stmt
;

r_value : expr
;

self_assignment : UPZ T_WORD P_EXCL P_EXCL increment_expr
                | NERFZ T_WORD P_EXCL P_EXCL increment_expr
                | TIEMZD T_WORD P_EXCL P_EXCL increment_expr
                | OVARZ T_WORD P_EXCL P_EXCL increment_expr
;

stmt : include               { printf("Inclusion (%s)", $1); }
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

stmts : stmt end_stmt
      | stmts stmt end_stmt
      | /* no statements at all */
;

then : end_stmt
     | P_QMARK end_stmt
     | end_stmt YARLY
     | P_QMARK end_stmt YARLY
;

%%
int main(int argc, char **argv)
{
  yyparse();
  return 0;
} 