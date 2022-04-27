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

/*
 *	@brief : read just on character from given file
 */
public char lexer_file_read_char(struct lexer *);

/*
 *	@brief : Move backward in a file , go to prev char in file, it will return true
 *	if we moved back and false when we are at start of file
 */
public bool lexer_file_prevchar(struct lexer *);

#endif
