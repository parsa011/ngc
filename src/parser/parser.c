/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser.h"
#include "statement.h"

public ASTnode *compile(lexer *l)
{
	select_lexer(l);
	if (interp_mode) {
		print_prompt();
	}
	next_token();
	ASTnode *n;
	do {
		n = parse_compound_statement();
		if (n)
			print_ast(n, 0);
	} while (n->type != A_EOF);
	return n;
}
