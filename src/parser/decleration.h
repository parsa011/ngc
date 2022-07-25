#ifndef _DECLERATION_H
# define _DECLERATION_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser_util.h"


/*
 *	@brief : parse variable decleration and add them to the symbol table
 *	@grammer :
 *
 *		declaration ::=  {declaration-specifier}+ {init-declarator}*
 */
public ASTnode *parse_variable_decleration();

#endif
