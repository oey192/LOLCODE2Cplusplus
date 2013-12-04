%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lolcode.tab.hpp"
%}


%%
BTW.+$                  { return COMMENT; }
[0-9]+                  { yylval.num = atoi(yytext); return T_NUMBER; }
A                       { return A; }
AND                     { return AND; }
BIGR                    { return BIGR; }
BYES                    { return BYES; }
CAN                     { return CAN; }
DIAF                    { return DIAF; }
GIMMEH                  { return GIMMEH; }
GTFO                    { return GTFO; }
HAI                     { return HAI; }
HAS                     { return HAS; }
I                       { return I; }
IM                      { return IM; }
IN                      { return IN; }
ITZ                     { return ITZ; }
IZ                      { return IZ; }
KTHX                    { return KTHX; }
KTHXBYE                 { return KTHXBYE; }
LETTAR                  { return LETTAR; }
LIEK                    { return LIEK; }
LINE                    { return LINE; }
LOL                     { return LOL; }
MAH                     { return MAH; }
NERF                    { return NERF; }
NERFZ                   { return NERFZ; }
NOT                     { return NOT; }
NOWAI                   { return NOWAI; }
OR                      { return OR; }
OUTTA                   { return OUTTA; }
OVAR                    { return OVAR; }
OVARZ                   { return OVARZ; }
R                       { return R; }
SMALR                   { return SMALR; }
STDIN                   { return STDIN; }
THAN                    { return THAN; }
TIEMZ                   { return TIEMZ; }
TIEMZD                  { return TIEMZD; }
UP                      { return UP; }
UPZ                     { return UPZ; }
VISIBLE                 { return VISIBLE; }
WORD                    { return WORD; }
XOR                     { return XOR; }
YARLY                   { return YARLY; }
YR                      { return YR; }
\?                      { return P_QMARK; }
\!                      { return P_EXCL; }
[A-Za-z]+               { yylval.str = strdup(yytext); return T_WORD; }
[.\n]                   { return NEWLINE; }
[\t ]+                  { /* Ignore whitespace */; }
%%