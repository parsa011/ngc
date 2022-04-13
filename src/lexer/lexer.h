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
#include "../token/token.h"
#include <stdio.h>

struct lexer {
	FILE *fp;
	char *file_name;
	char current_char;
	char put_back_char;

	struct position pos;
	struct position prevpos;

	struct token tok;

	/* I/O functions */
	void (*open_file)(struct lexer *, char *);
	void (*close_file)(struct lexer *);
};

#define get_lexer_put_back(l) (l->put_back_char)

/*
 *	pointer to lexer that we are working with
 */
private struct lexer *working_lexer; 

/*
 *	@brief : Init new lexer, open file by give name and return pointer to lexer
 *		- name of file to open in lexer
 */
public struct lexer *lexer_init();

/*
 *	@brief : set working_lexer variable to given lexer pointer
 */
public void set_working_lexer(struct lexer *);

/*
 *	@brief : test if give lexer is working_lexer
 */
public bool is_current_lexer(struct lexer *l);

/*
 *	@brief : lex given lexer and find new token of it
 *	> make sure that you set target lexer and working_lexer by calling set_working_lexer before
 *	  using this function, because it will panic if given lexer is not working_lexer
 */
public void lex(struct lexer *l);

/*
 *	@brief : Clsoe given lexer
 */
public void lexer_close(struct lexer *);

/*
 *	@brief : Return new char from given file, but If There isn't Anything Saved Char
 */
private char next_char();

/*
 *	@brief : Put back given Char, To get it after new new_char call
 */
private void put_back(char);

/*
 *	@brief : Skip White spaces And and put_back last non space char to give it from next_char
 */
private char skip_whitespace();

/*
 *	@brief : Eat One line Comment, skip until new \n :)
 */
private void skip_ol_comment();

/*
 *	@brief : Skipt Multiline comments
 */
private void skip_ml_comment();

#endif
