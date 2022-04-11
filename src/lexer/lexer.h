#ifndef _LEXER_H
# define _LEXER_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*	
*	first phase of compiler
*/

#include "../ngc.h"
#include <stdio.h>

struct lexer {
	FILE *fp;
	char *file_name;
	char current_char;
	/* contains current text of input file */
	char *buf;
	size_t buflen; // Length of buffer currently used
	size_t alloc;  // Space allocated for buffer

	struct position pos;
	struct position prevpos;

};

/*
 *	@brief : Init new lexer, open file by give name and return pointer to lexer
 *		- name of file to open in lexer
 */
public struct lexer *lexer_init(char *);

/*
 *	@brief : Clsoe given lexer
 *		- lexder to clsoe and free
 */
public void lexer_close(struct lexer *);

/*
 *	@brief : Return new char from given file, but If There isn't Anything Saved Char
 */
private char next_char();

/*
 *	@brief : Put back given Char, To get it after new new_char call
 *		- char to put back
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

/*
 *	@brief : Return next token as pointer from give lexer
 *		- lexer to read it file
 */
public struct token *lexer_next(struct lexer *);

#endif
