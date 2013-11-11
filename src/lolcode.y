%{
#include <string>
#include "lolcode.h"
void yyerror(const char *str);
int yywrap();
int yylex();
%}

%token TERM NOOB NUMBR NUMBAR YARN HAI KTHXBYE I_HAZ_A ITZ R IF_U_SAY_SO HOW_DUZ_I YR AN MKAY OIC O_RLY YA_RLY MEBBE NO_WAI IM_IN_YR IM_OUTTA_YR FOUND_YR GTFO


start:
    beg TERM
    block
    end TERM
    { $$ = $3 }

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
    statemente
    |
    statemente block
    ;

statemente:
    statement TERM
    ;

statement:
    declare
    |
    assign
    |
    function
    |
    if
    |
    switch
    |
    expression
    ;

declare:
    I_HAZ_A var
    |
    I_HAZ_A var ITZ expression
    ;

assign:
    var R expression
    ;

function:
    funcbegin TERM block IF_U_SAY_SO
    ;

funcbegin:
    HOW_DUZ_I var
    |
    funcbegin2
    ;

funcbegin2:
    funcbegin YR var
    |
    funcbegin2 AN YR var
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
    var
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
    IM_OUTTA_YR var

startloop:
    IM_IN_YR var operation YR var
    |
    IM_IN_YR var operation YR var TIL expression
    |
    IM_IN_YR var operation YR var WILE expression
    ;




