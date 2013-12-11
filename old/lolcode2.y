%{
//-- C declarations --------------------------------------
#include string
#include "lolcode.h"
void yyerror(const char *str);
int yywrap();
int yylex();
%}

//-- Bison declarations ----------------------------------
%token TERM NOOB NUMBR NUMBAR TROOF YARN HAI KTHXBYE I_HAZ_A ITZ R IF_U_SAY_SO HOW_DUZ_I YR AN MKAY OIC O_RLY YA_RLY MEBBE NO_WAI IM_IN_YR IM_OUTTA_YR FOUND_YR GTFO VAR WON_OF EITHER_OF BOTH_OF SMALLR_OF BIGGR_OF WILE TIL UPPIN NERFIN MOD_OF QUOSHUNT_OF PRODUKT_OF DIFF_OF NOT SUM_OF ANY_OF ALL_OF BOTH_DIFFRINT BOTH_SAEM
%left BIGGR_OF SMALLR_OF BOTH_OF EITHER_OF WON_OF BOTH_SAEM BOTH_DIFFRINT
%left SUM_OF DIFF_OF
%left PRODUKT_OF QUOSHUNT_OF MOD_OF
%left NOT

%%

//-- GRAMMAR RULES ---------------------------------------

program: 				"HAI" command_list "KTHXBYE"

command_list:    		/* empty */
					| command command_list

command: 			  	/* empty */
					| variable_declaration
			     	| variable_assignment
			     	| variable_explicit_cast
			     	| variable_expression
			     	| standard_io
			     	| conditionals
			     	| loops
			     	| function_definition
			     	;

standard_io:    		/* empty */
					| "VISIBLE" infinite_arity_io
                		| "GIMMEH" variable_name
                		;

infinite_arity_io:  	/* empty */
					| "!" statement_end
                    	| variable_expression infinite_arity_io
                    	;

statement_end:  		/* empty */
					| "\r\n"
                		| "\r"
                		| "\n"
                		| ","
                		;

variable_declaration: 	"I HAS A" variable_name "ITZ" variable_expression

variable_assignment: 	variable_name "R" variable_expression

variable_explicit_cast: 	variable_name "IS NOW A" variable_type

function_name:
variable_name: 		"[a-zA-Z][a-zA-Z0-9_]*"

variable_expression:    	| math_operator
                        	| boolean_operator
                        	| variable_value
                        	| string_concat
                        	| variable_inferred_cast
                        	| function_call
                        	;

variable_value: 		| "WIN"
                		| "FAIL"
                		| "-""0-9+"
		      		| "-""0-9*.0-9+"
//              		| "\"\S*\""
					;

math_operator:	 		| "SUM OF" variable_expression "AN" variable_expression
                		| "DIFF OF" variable_expression "AN" variable_expression
                		| "PRODUKT OF" variable_expression "AN" variable_expression
                		| "QUOSHUNT OF" variable_expression "AN" variable_expression
                		| "MOD OF" variable_expression "AN" variable_expression
                		| "BIGGR OF" variable_expression "AN" variable_expression
                		| "SMALLR OF" variable_expression "AN" variable_expression
                		;

boolean_operator:   	| "BOTH OF" variable_expression "AN" variable_expression
                    	| "EITHER OF" variable_expression "AN" variable_expression
                    	| "WON OF" variable_expression "AN" variable_expression
                    	| "NOT" variable_expression
                    	| "ALL OF" infinite_arity
                    	| "ANY OF" infinite_arity
                    	;

comparison_operator:    	| "BOTH SAEM" variable_expression "AN" variable_expression
                        	| "DIFFRINT" variable_expression "AN" variable_expression
                        	;

infinite_arity: 		| "MKAY"
                		| variable_expression "AN" infinite_arity
                		;
                
string_concat:			"SMOOSH" infinite_arity

variable_inferred_cast: 	"MAEK" variable_expression "A" variable_type

variable_type:  		| "TROOF"
                		| "YARN"
                		| "NUMBR"
                		| "NUMBAR"
                		| "NOOB"
                		;

conditionals:   		| "O RLY?" if_then if_elseif if_else "OIC"
                		| "WTF?" switch_case switch_default "OIC"
                		;

if_then: 				"YA RLY" command_list

if_else: 				"NO WAI" command_list

if_elseif: 			"MEBBE" variable_expression command_list if_elseif

switch_case: 			"OMG" variable_value command_list switch_case

switch_default: 		"OMGWTF" command_list

loops: 				"IM IN YR" variable_name loop_operation loop_termination
    					command_list
    					"IM OUTTA YR" variable_name
    					;

loop_operation: 		| "UPPIN YR" variable_name
                		| "NERFIN YR" variable_name
                		;

loop_termination:   	| "TIL" variable_expression
                    	| "WILE" variable_expression
                    	;

function_definition:    	"HOW DUZ I" function_name function_arguments
                        	function_command_list
                        	"IF U SAY SO"
                        	;

function_arguments: 	  "YR" variable_name
					| "AN" function_arguments
					;

function_command_list:  	| "FOUND YR" variable_expression
                        	| "GTFO"
                        	| command_list
                        	;

function_call: 		function_name function_call_arguments

function_call_arguments: variable_expression function_call_arguments
