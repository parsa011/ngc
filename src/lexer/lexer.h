#ifndef _LEXER_H
# define _LEXER_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "../ngc.h"
#include <stdio.h>

struct lexer {
	FILE *fp;
	char *file_name;
	char current_char;
	struct position pos;
	struct position prevpos;
};

/*
 *	@brief : Return new char from given file, but If There isn't Anything Saved Char
 */
private char next_char();

/*
 *	@brief : Put back given Char, To get it after new new_char call
 */
private void put_back(int);

/*
 *	@brief : Skip White spaces And and put_back last non space char to give it from next_char
 */
private void skip_whitespace();

/*
 *	@brief : Eat One line Comment, skip until new \n :)
 */
private void skip_ol_comment();

/*
 *	@brief : Skipt Multiline comments
 */
private void skip_ml_comment();

#endif
