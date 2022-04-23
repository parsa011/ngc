/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser.h"

private struct lexer *working_lexer;

private void select_lexer(struct lexer *l)
{
	working_lexer = l;
	set_working_lexer(l);
}

public struct ASTnode *compile(struct lexer *l)
{
	select_lexer(l);
	next_token();
	struct ASTnode *n;
	return n;
}
