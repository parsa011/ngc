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

private void statements(struct ASTnode *n)
{

}

public struct ASTnode *compile(struct lexer *l)
{
	select_lexer(l);
	next_token();
	while (current_token.type != T_EOF) {
		print_token(&current_token);
		next_token();
	}
	printl("DONE");
	struct ASTnode *n;
	statements(n);
	return n;
}
