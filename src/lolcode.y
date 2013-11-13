%{
#include <string>
#include "lolcode.h"
void yyerror(const char *str);
int yywrap();
int yylex();
%}

%token TERM NOOB NUMBR NUMBAR YARN HAI KTHXBYE I_HAZ_A ITZ R IF_U_SAY_SO HOW_DUZ_I YR AN MKAY OIC O_RLY YA_RLY MEBBE NO_WAI IM_IN_YR IM_OUTTA_YR FOUND_YR GTFO VAR


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
    operator
    |
    VAR
    |
    value
    |
    AN
    |
    MKAY
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

//TODO: add operator stuff
operator:
    

    ;

//could also be any unary function (e.g. not) but I'm not bothering to implement that for now
operation:
    UPPIN
    |
    NERFIN
    ;


