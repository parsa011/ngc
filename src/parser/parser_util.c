/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser_util.h"
#include "parser.h"

public void match(token_type type, char *msg)
{
	if (current_token.type != type) {
		printf("Error %s\n", msg);
	}
	next_token();
}

public void semi()
{
	match(T_SEMI, "Semicolon Expected");
}
