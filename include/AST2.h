#ifndef _AST2_H_
#define _AST2_H_

#include <string>

enum VariableType {None,Int,String}; // FOR LOLCODE4.Y
enum FormatOptions {FORMAT_NONE = 0x0,FORMAT_EOL = 0x1,FORMAT_INDENT = 0x2}; //FOR LOLCODE4.Y
int yyerror(const char *s); //Redeclared so it stops bitching at me
int yylex();

//FOLLOWING ARE PLACE HOLDERS SO I CAN MAKE SURE THE PARSER IS WORKING CORRECTLY
int yyerror(const char *STRING);
int yylex();
void GEN_PROGRAM_START();
void GEN_PROGRAM_END();
void GEN_PRINT(const std::string &STRING);
void GEN_INPUT(const std::string &VARIABLE);
void GEN_DECLARE_VAR(const std::string& NAME, const std::string& VALUE, VariableType TYPE, int OPTION = FORMAT_EOL | FORMAT_INDENT);
void GEN_ASSIGN_VAR(const std::string& NAME, const std::string& VALUE, VariableType TYPE);
std::string GEN_OPERATOR(const std::string& OPERATOR, const std::string& A, const std::string& B);
std::string GEN_FUNCTION(const std::string& FUNCTION, const std::string& A, const std::string& B);
void GEN_FOR_START(const std::string& VARIABLE, const std::string& CONDITION, const std::string& MODE);
void GEN_FOR_END();
void GEN_BREAK();
void GEN_IF_START(const std::string& CONDITION);
void GEN_IF_ELSE();
void GEN_IF_ELSE_IF(const std::string& CONDITION);
void GEN_CONDITIONAL_END();
void GEN_SWITCH_START(const std::string& CONDITION);
void GEN_SWITCH_CASE_START(const std::string& OPTION);
void GEN_SWITCH_DEFAULT_START();
void GEN_SWITCH_CASE_END();
#define YYSTYPE_IS_DECLARED 1
typedef std::string YYSTYPE;
extern int _indent;

#endif
