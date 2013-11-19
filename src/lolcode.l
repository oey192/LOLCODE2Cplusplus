%{
    #include "lolcode.tab.h"
    /*std::map < string , int > reserved;
    #define RESERVE(t) reserved[tolower(#t)]=t
    void setup()
    {
 		RESERVE(this);
 		RESERVE(that);
    }*/
%}
%%

//Math
AN                      {
    return AN;
}
MKAY                    {
    
}
//comments
BTW                     {
    
}
OBTW.*TLDR              {
    
}
//variable declaration, library importing, etc
CAN HAZ                 {
    
}
I HAZ A                 {
    
}
ITZ                     {
    
}
IZ                      {
    
}
//loops
IM IN YR                {
    
}
IM OUTTA YR             {
    
}
//stdio stuffs
VISIBLE					{
	
}
GIMMEH					{
	
}
[\n,]+					{
	return TERM;
}
//beg and end of kittez!
HAI                     {
    
}
KTHXBYE                 {
    
}
//user literals
[0-9]*\.[0-9]+          {
    yyval = ASTNodeSP(new ASTNumbar(atof(yytext)));
    return NUMBAR
}
[0-9]                   {
	yyval = ASTNodeSP(new ASTNumbr(atoi(yytext)));
    return NUMBR;
}
WIN | FAIL              {
    return TROOF
}
[a-zA-Z_][a-zA-Z0-9_]*  {
    yyval = ASTNodeSP(new ASTVar(yytext));
}
".*"                    {
    
}

%%