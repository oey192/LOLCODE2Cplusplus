%{
#include <string>
#include "lolcode.h"
void yyerror(const char *str);
int yywrap();
int yylex();
%}

%token TERM NOOB NUMBR NUMBAR TROOF YARN HAI KTHXBYE I_HAZ_A ITZ R IF_U_SAY_SO HOW_DUZ_I YR AN MKAY OIC O_RLY YA_RLY MEBBE NO_WAI IM_IN_YR IM_OUTTA_YR FOUND_YR GTFO VAR WON_OF EITHER_OF BOTH_OF SMALLR_OF BIGGR_OF WILE TIL UPPIN NERFIN MOD_OF QUOSHUNT_OF PRODUKT_OF DIFF_OF NOT SUM_OF ANY_OF ALL_OF BOTH_DIFFRINT BOTH_SAEM

%%

start:
    beg TERM
    block
    end TERM
    { $$ = $3 }
    ;

beg:
    HAI
    |
    HAI NUMBAR
    ;

end:
    KTHXBYE
    |
    KTHXBYE TERM
    ;


block:
    statementt
    |
    statementt block
    ;

statementt:
    statement TERM
    ;

//switch ommitted
statement:
    declare
    |
    assign
    |
    function
    |
    ifmaster
    |
    loop
    |
    expression
    ;

declare:
    I_HAZ_A VAR
    |
    I_HAZ_A VAR ITZ expression
    ;

assign:
    VAR R expression
    ;

function:
    funcbegin TERM block IF_U_SAY_SO
    ;

funcbegin:
    HOW_DUZ_I VAR
    |
    funcbegin2
    ;

funcbegin2:
    funcbegin YR VAR
    |
    funcbegin2 AN YR VAR
    ;


ifmaster:
    if OIC
    |
    if else OIC
    |
    if elseif else OIC
    ;

if:
    expression TERM
    O_RLY TERM
    YA_RLY TERM
    block
    endif
    ;

endif:
    OIC
    |
    else OIC
    |
    elseif else OIC
    ;

else:
    NO_WAI TERM
    block
    ;

elseif:
    MEBBE TERM
    block
    |
    elseif
    elseif
    ;

expression:
    expr
    |
    expr expression
    ;

expr:
    operator expression AN expression
    |
    inf_op expression AN inf_expr MKAY
    |
    NOT expression
    |
    VAR
    |
    value
    |
    AN
    |
    MKAY
    ;

inf_expr:
    expression
    |
    inf_expr AN inf_expr
    ;


loop:
    startloop
    block
    IM_OUTTA_YR VAR

startloop:
    IM_IN_YR VAR operation YR VAR
    |
    IM_IN_YR VAR operation YR VAR TIL expression
    |
    IM_IN_YR VAR operation YR VAR WILE expression
    ;


operator:
    SUM_OF
    |
    DIFF_OF
    |
    PRODUKT_OF
    |
    QUOSHUNT_OF
    |
    MOD_OF
    |
    BIGGR_OF
    |
    SMALLR_OF
    |
    BOTH_OF
    |
    EITHER_OF
    |
    WON_OF
    |
    BOTH_SAEM
    |
    BOTH_DIFFRINT
    ;

inf_op:
    ALL_OF
    |
    ANY_OF
    ;

//could also be any unary function (e.g. not) but I'm not bothering to implement that for now
operation:
    UPPIN
    |
    NERFIN
    ;

value:
    NUMBAR
    |
    NUMBR
    |
    TROOF
    |
    YARN
    ;

%%


void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}
 
int yywrap()
{
        return 1;
} 
  
int main(int argc, char *argv[])
{
        yyparse();
        return 0;
}

