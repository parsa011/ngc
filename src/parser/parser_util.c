/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser_util.h"

lexer *current_lexer;

public void select_lexer(lexer *l)
{
	current_lexer = l;
	lexer_set_working_lexer(l);
}

public void match(token_type type, char *msg)
{
	if (current_token.type != type) {
		show_lexer_error(msg);
	}
	next_token();
}

public void semi()
{
	match(T_SEMI, "Semicolon Expected Before Current Token");
}

public void left_paren()
{
	match(T_OP_P, "'(' Expected");
}

public void right_paren()
{
	match(T_CL_P, "')' Expected");
}

public void assign_token()
{
	if (!is_assign_token(current_token.type)) {
		show_lexer_error("Assign Token Expected");
		panic(NULL);
	}
	next_token();
}

public bool is_eof()
{
	return current_token.type == T_EOF;
}

public bool is_type_keyword(bool go_next)
{
	bool res = false;
	if (is_type_token(current_token.type)) {
		res = true;
	}
	if (go_next)
		next_token();
	return res;
}

public bool is_qualifier(bool go_next)
{
	bool res = false;
	switch (current_token.type) {
		case T_CONST :
		case T_VOLATILE :
		case T_UNSIGNED :
			res = true;
	}
	if (go_next)
		next_token();
	return res;
}

public bool is_endof_expression()
{
	int tokentype = current_token.type;
	return tokentype == T_SEMI  || tokentype == T_CL_P || tokentype == T_COMMA;
}

public void skip_token_until(token_type type)
{
	while (current_token.type != type) {
		if (is_eof()) {
			printf("Expcted '%s', But Didnt Found Until EOF\n", get_token_str(type));
			break;
		}
		next_token();
	}
}

public bool token_is(token_type tp)
{
	return current_token.type == tp;
}
