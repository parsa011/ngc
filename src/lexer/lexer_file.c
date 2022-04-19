/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*
*	we manager file associated task of lexer here like open, close, read, unget and ....
*/

#include "lexer_file.h"
#include <assert.h>

public void lexer_open_file(struct lexer *l, char *file_name)
{
	l->fp = fopen(file_name, "r");
	if (!l->fp) {
		// TODO : panic here
		return ;
	}
	l->file_name = basename(file_name);
}

public void lexer_close_file(struct lexer *l)
{
	assert(l->fp);
	fclose(l->fp);
	l->file_name = 0;
}

public char lexer_file_read_char(FILE *fp)
{
	return fgetc(fp);
}
