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

private void statements(struct ASTnode *n)
{
	while (!is_eof()) {
		switch (current_token.type) {

			case T_IDENT :
				parse_assign_variable();
				break;

			default :
				if (is_type_keyword(false)) {
					declare_varaiable();
				}
				break;

		}
		if (interp_mode) {
			print_prompt();
		}
		semi();
	}
}

private struct ASTnode *declare_varaiable()
{
	int tokentype = current_token.type;
	if (!is_type_keyword(true)) {
		show_lexer_error("Error : Type Expected");
		panic(NULL);
	}
	/*
	 *	a helpful note : 
	 *	we have to prepare our type here , because when we are declaring many variables in one line,
	 *	they have same type, so it's usefule to declare our type here and use it when we are adding
	 *	variable to symbol table
	 *
	 *		const int age, count;
	 *
	 *	our type is constant integer
	 */
	struct type tp = {
		.type = tokentype,
		.is_pointer = false
	};

decl_again:

	/* here we should check for star , if current token is an star so our type is a pointer to 
	 * then we have to edit our type but for now we skip them
	 */
	if (current_token.type == T_STAR) {
		tp.is_pointer = true;
		next_token();
	} else
		tp.is_pointer = false;

	if (current_token.type != T_IDENT) {
		show_lexer_error("Identifier Expected");
		panic(NULL);
	}
	/* save current position because we will call next_token() and it will change our position 
	 * this position is starting point of identifier
	 *
	 *	int age = 10;
	 *	    ^
	 * current position is here
	 */
	struct position pos;
	pos_copy(current_token.pos, pos);
	char *text = strdup(current_token.buffer);
	next_token();

	struct ASTnode *value = NULL;
	/* TODO : parse Rvalue by considering typeof variable */
	if (current_token.type == T_EQUAL) { 	
		/* token is '=' so we have to assign a value to variable */
		next_token();
	
		value = get_rvalue_for_type(tokentype, tp);
	}
	symtab_create_integer(text, value ? calculate_binary_tree(value) : 0, &tp, pos);
	if (current_token.type == T_COMMA) {
		/*
		 * int age = 10, count;
		 *             ^
		 * we are here and we want to declare another variable again
		 */
		next_token();
		goto decl_again;
	}
	free(text);
}

private struct ASTnode *parse_assign_variable()
{
	struct symtab_entry *entry = symtab_get_by_name(current_token.buffer);
	struct ASTnode *left = create_ast_leaf(strdup(entry->name), A_IDENT, entry->integer, current_token.pos);
	match(T_IDENT, "Identifier Expected");
	// TODO : all assign token should be valid like += , -= and ...
	assign_token();
	int value = calculate_binary_tree(parse_binary_expression(0));
	struct ASTnode *rigth = create_ast_leaf("RVALUE", A_INTLIT, value, current_token.pos);
	struct ASTnode *tree = create_ast_node("ASSIGN", A_ASSIGN, 0, left, rigth, current_token.pos);
	// changin symbol integer value for now
	// TODO : check assign operator type , like -= , += and ...
	// TODO
	entry->integer = value;
	return tree;
}

/*
 *	get value for a type , for example for int literals and ...
 *
 *		int age = expr;
 *
 *		char ch = iden | 'c';
 *
 * 		char *name = "parsa";
 *
 *	also we need type for more information , for example we can get singend value
 *	for unsinged variables , or we should take an memory address instead of a binexpr
 *	for pointers
 *	
 * 	and then it will return an AST
 */
private struct ASTnode *get_rvalue_for_type(token_type type, struct type info)
{
	struct ASTnode *res = NULL;
	/*	TODO : check for pointers
	 */
	if (info.is_pointer) {
	}
	switch (type) {

		case T_INT :
		case T_DOUBLE :
		case T_FLOAT :
			res = parse_binary_expression(0);
			break;

		case T_CHAR :
			res = parse_char_literal();
			break;

	}
	return res;
}

// TODO
private struct ASTnode *parse_char_literal()
{
	next_token();
	return NULL;
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

		case T_IDENT :
			{
				// TODO : type checking , we need that
				struct symtab_entry *entry = symtab_get_by_name(current_token.buffer);
				next_token();
				n = create_ast_leaf(current_token.buffer, A_INTLIT, entry->integer, current_token.pos);
				return n;
			}

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
	if (is_endof_binexpr())
		goto return_ast;
	struct token *token_copy;
	while (token_precedence(tokentype) > ptp) {

		token_copy = token_duplicate(&current_token);
		next_token();
		right = parse_binary_expression(token_precedence(tokentype));
		left = create_ast_node(token_copy->buffer, tokentype_to_nodetype(tokentype), current_token.integer, left, right, token_copy->pos);

		tokentype = current_token.type;
		if (is_endof_binexpr())
			break;
	}
return_ast:
	return left;
}
