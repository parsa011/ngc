#ifndef _LEXER_FILE_H
# define _LEXER_FILE_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "../ngc.h"
#include "lexer.h"

/*
 *	@brief : open file by name into given lexer
 */
public void lexer_open_file(struct lexer *, char *);

/*
 *	@brief : close given lexer file
 */
public void lexer_close_file(struct lexer *);

#endif
