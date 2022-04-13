/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "lexer_file.h"
#include <assert.h>

public void lexer_open_file(struct lexer *l, char *file_name)
{
	l->fp = fopen(file_name, "r");
	if (!l->fp) {
		// TODO : panic here
		printf("File <'%s'> Not Found\n", file_name);
		return ;
	}
	l->file_name = file_name;
}

public void lexer_close_file(struct lexer *l)
{
	assert(l->fp);
	fclose(l->fp);
	l->file_name = 0;
}
