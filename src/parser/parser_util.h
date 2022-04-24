#ifndef _PARSER_UTIL_H
# define _PARSER_UTIL_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*
*	Some utily functions for parser like match token and ...
*/

#include "symtab.h"

/*
 *	@brief : check if current token type is equals to given type , if is's not , will print
 *	given message to output
 */
public void match(token_type, char *);

/*
 *	@brief : check if current token is semicolon , it will use match with some default args to check , nothing  more :)
 */
public void semi();

#endif
