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
 *	@brief : This is entry point of parser , we will call this everwhere that we need
 *	to compiler file
 */
public ASTnode *compile(lexer *);

/*
 *	@brief : Parse Declare variable statements
 */
private ASTnode *declare_variable();

/*
 *	@brief : process and assign values to variables
 */
private ASTnode *parse_assign_variable();



#endif
