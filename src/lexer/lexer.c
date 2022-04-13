/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "lexer.h"
#include "lexer_file.h"

public struct lexer *lexer_init()
{
	struct lexer *l = ngc_malloc(sizeof(struct lexer));
	l->open_file = &lexer_open_file;
	l->close_file = &lexer_close_file;
	return l;
}

