#ifndef _STATEMENT_H
# define _STATEMENT_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*
*	Parser Statement
*/

#include "parser_util.h"

/*
 *	@brief : Parse a compund statement 
 *	@grammer :
 *
 *		compound-statement ::= '{' {declaration}* {statement}* '}'
 *
 *	Compound Statements Starts with a '{' and ends with '}'
 *	They can be Nested
 */
public ASTnode *parse_compound_statement();

/*
 *	@brief : Parse Single statement , means just one line
 *	@grammer :
 *
 * 		statement ::= labeled-statement
 *					| expression-statement
 *					| compound-statement
 *					| selection-statement
 *					| iteration-statement
 *					| jump-statement
 */
public ASTnode *parse_statement();

/*
 *	@brief : parse if statement for debug mode, we will have this function only
 *		when program is in DEBUG mode
 *	@grammer :
 *
 *		print-statement ::= 'print' expression ';'
 */
public ASTnode *parse_print_statement();

/*
 *	@brief : ---
 *	@grammer : 
 *
 *		if-statement ::= 'if' '(' expression ')' statement
 *				       | 'if' '(' expression ')' statement 'else' statement
 */
public ASTnode *parse_if_statement();

#endif
