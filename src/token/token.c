/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "token.h"


/*
 *	TODO : panic if id was out or token_type_str array range
 */
public char *get_token_str(int id)
{
	return token_type_str[id];
}
