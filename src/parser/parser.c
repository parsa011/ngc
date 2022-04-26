/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser.h"

private void statements(struct ASTnode *n)
{
	while (!is_eof()) {
		//switch (current_token.type) {
		//	case T_HASHTAG :
		//		skip_token_until(T_GT);
		//		next_token();
		//		break;
		//}
		print_token(&current_token);
		next_token();
	}
}

public struct ASTnode *compile(struct lexer *l)
{
	select_lexer(l);
	next_token();
	//while (current_token.type != T_EOF) {
	//	print_token(&current_token);
	//	next_token();
	//}
	struct ASTnode *n;
	statements(n);
	return n;
}
