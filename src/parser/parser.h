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

/*
 *	@brief : checks current token to determine what to do now
 */
private void statements();

/*
 *	@breif : return primay factor as a ASTnode tree
 */
private struct ASTnode *primary_factor(int);

/*
 *	@brief : parse binary expression by pratt parsing algorithm
 */
private struct ASTnode *parse_binary_expression(int);

/*
 *	@brief : This is entry point of parser , we will call this everwhere that we need
 *	to compiler file
 */
public struct ASTnode *compile(struct lexer *);

#endif
