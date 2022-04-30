/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser.h"
#include "symtab.h"
#include "../token/token.h"
#include "../ast/ast.h"

private void statements(struct ASTnode *n)
{
	while (!is_eof()) {
		if (is_type_keyword(false)) {
			declare_varaiable();
		} else {
			struct ASTnode *n = parse_binary_expression(0);
			printf("%d\n", calculate_binary_tree(n));
		}
		if (interp_mode) {
			print_prompt();
		}
		semi();
	}
}

public struct ASTnode *declare_varaiable()
{
	if (!is_type_keyword(true)) {
		show_lexer_error("Error : Type Expected");
		panic(NULL);
	}
decl_again:
	if (current_token.type != T_IDENT) {
		show_lexer_error("Identifier Expected");
		panic(NULL);
	}
	char *text = strdup(current_token.buffer);
	next_token();
	struct ASTnode *value = NULL;
	/* TODO : parse Rvalue by considering typeof variable */
	if (current_token.type == T_EQUAL) { 	/* token is '=' so we have to assign a value to variable */
		next_token();
		value = parse_binary_expression(0);
		//print_ast(n, 0);
	}
	symtab_create_integer(text, value ? calculate_binary_tree(value) : 0, current_token.pos);
	if (current_token.type == T_COMMA) {
		next_token();
		goto decl_again;
	}
	free(text);
}

private struct ASTnode *primary_factor(int ptp)
{
	struct ASTnode *n;
	switch (current_token.type) {

		case T_INTLIT :
			n = create_ast_leaf(current_token.buffer, A_INTLIT, current_token.integer, current_token.pos);
			next_token();
			return n;

		case T_OP_P :
			next_token();
			n = parse_binary_expression(0);
			match(T_CL_P, "Unclosed Parenthesis");
			return n;

		default :
			show_lexer_error("Bad Token");
			panic(NULL);
			break;

	}
	return NULL;
}

private struct ASTnode *parse_binary_expression(int ptp)
{
	struct ASTnode *right, *left;
	left = primary_factor(ptp);
	int tokentype = current_token.type;
	if (tokentype == T_EOF || tokentype == T_SEMI || tokentype == T_CL_P || tokentype == T_COMMA)
		return left;
	struct token *token_copy;
	while (token_precedence(tokentype) > ptp) {

		token_copy = token_duplicate(&current_token);
		next_token();
		right = parse_binary_expression(token_precedence(tokentype));
		left = create_ast_node(token_copy->buffer, tokentype_to_nodetype(tokentype), current_token.integer, left, right, token_copy->pos);

		tokentype = current_token.type;
		if (tokentype == T_EOF || tokentype == T_SEMI  || tokentype == T_CL_P || tokentype == T_COMMA)
			break;
	}
	return left;
}

public struct ASTnode *compile(struct lexer *l)
{
	select_lexer(l);
	if (interp_mode) {
		print_prompt();
	}
	next_token();
	struct ASTnode *n = NULL;
	statements(n);
	return n;
}
