%{
    #include "lolcode.tab.hpp"
    /*std::map < string , int > reserved;
    #define RESERVE(t) reserved[tolower(#t)]=t
    void setup()
    {
 		RESERVE(this);
 		RESERVE(that);
    }*/
%}
%%

AN                      {
    return AN;
}
MKAY                    {
    printf("got an MKAY");
}
BTW                     {
    printf("got a BTW");
}
OBTW.*TLDR              {
    printf("got a Comment");
}
"CAN HAZ"                 {
    printf("got a CAN_HAZ");
}
"I HAZ A"                 {
    printf("got a I_HAZ_A");
}
ITZ                     {
    printf("got a ITZ");
}
IZ                      {
    printf("got a IZ");
}
"IM IN YR"                {
    printf("got a IM_IM_YR");
}
"IM OUTTA YR"             {
    printf("got a IM_OUTTA_YR");
}
VISIBLE					{
	printf("got a VISIBLE");
}
GIMMEH					{
	printf("got a GIMMEH");
}
[\n,]+					{
    printf("got a TERM");
	return TERM;
}
HAI                     {
    printf("got a HAI");
}
KTHXBYE                 {
    printf("got a KTHXBYE");
}
[0-9]*\.[0-9]+          {
    /* yylval = ASTNodeSP(new ASTNumbar(atof(yytext))); */
    printf("got a NUMBAR");
    return NUMBAR;
}
[0-9]                   {
	/* yylval = ASTNodeSP(new ASTNumbr(atoi(yytext))); */
    printf("got a NUMBR");
    return NUMBR;
}
WIN|FAIL              {
    printf("got a troof\n");
    return TROOF;
}
[a-zA-Z_][a-zA-Z0-9_]*  {
    /* yylval = ASTNodeSP(new ASTVar(yytext)); */
    printf("got a var\n");
}
".*"                    {
    
}

%%