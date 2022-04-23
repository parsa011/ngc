#ifndef _PARSER_H
# define _PARSER_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "../ngc.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"

/*
 *	this is like our lexer, it will point to our working lexer , so we can have access
 *	to lexer taht we are working with , in all parsing function
 */
private struct lexer *working_lexer;

#define next_token() (lex(working_lexer))
#define current_token working_lexer->tok

/*
 *	@brief : set working lexer to given lexer, and also activate given lexer in lexer phase
 *	by calling set_working_lexer()
 */
private void select_lexer(struct lexer *);

/*
 *	@brief : This is entry point of parser , we will call this everwhere that we need
 *	to compiler file
 */
public struct ASTnode *compile(struct lexer *);

#endif
