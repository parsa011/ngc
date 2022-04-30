/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser_util.h"

struct lexer *current_lexer;

public void select_lexer(struct lexer *l)
{
	current_lexer = l;
	lexer_set_working_lexer(l);
}

public void match(token_type type, char *msg)
{
	if (current_token.type != type) {
		printf("Error : %s\n", msg);
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

public void semi()
{
	//if (current_token.type != T_SEMI) {
	//	show_lexer_error("Semicolon Expected");		
	//}
	//next_token();
	match(T_SEMI, "Semicolon Expected");
}
