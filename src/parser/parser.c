/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser.h"
#include "../token/token.h"
#include "../ast/ast.h"

private void statements(struct ASTnode *n)
{
	while (!is_eof()) {
		struct ASTnode *n = parse_binary_expression(0);
		print_ast(n, 0);
		printf("Result is : %d\n", calculate_binary_tree(n));
		next_token();
	}
}

private struct ASTnode *primary_factor()
{
	struct ASTnode *n;
	switch (current_token.type) {

		case T_INTLIT :
			n = create_ast_leaf(current_token.buffer, A_INTLIT, current_token.integer, current_lexer->pos);
			next_token();
			return n;

		case T_OP_P :
			next_token();
			n = parse_binary_expression(0);
			match(T_CL_P, "Unclosed Parenthesis");
			return n;
	}
	return NULL;
}

private struct ASTnode *parse_binary_expression(int ptp)
{
	struct ASTnode *right, *left;
	left = primary_factor();
	int tokentype = current_token.type;
	if (tokentype == T_EOF || tokentype == T_SEMI)
		return left;
	struct token *token_copy;
	while (token_precedence(tokentype) > ptp) {

		token_copy = token_duplicate(&current_token);

		next_token();

		right = parse_binary_expression(token_precedence(tokentype));
		left = create_ast_node(token_copy->buffer, tokentype_to_nodetype(tokentype), current_token.integer, left, right, token_copy->pos);

		tokentype = current_token.type;
		if (tokentype == T_EOF || tokentype == T_SEMI)
			break;
	}
	return left;
}

public struct ASTnode *compile(struct lexer *l)
{
	select_lexer(l);
	next_token();
	struct ASTnode *n;
	statements(n);
	return n;
}
