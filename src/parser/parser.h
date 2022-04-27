#ifndef _PARSER_H
# define _PARSER_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser_util.h"

private void statements();

private struct ASTnode *primary_factor(int);

private struct ASTnode *parse_binary_expression(int);

/*
 *	@brief : This is entry point of parser , we will call this everwhere that we need
 *	to compiler file
 */
public struct ASTnode *compile(struct lexer *);

#endif
