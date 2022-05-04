/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser.h"

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
	/*
	 * have a copy of varaible name  because we gonna need that when we want to create a symbol for it
	 */
	char *text = strdup(current_token.buffer);
	/* skip variabel name */
	next_token();
	/*
	 * check if current token is assign token or no 
	 * if it is , so we gonna parse right value
	 */
	struct ASTnode *rval_tree;
	union value val;
	val.intval = 0;
	val.realval = 0;
	if (current_token.type == T_EQUAL) {
		next_token();
		/* TODO : parse Rvalue by considering typeof variable */
		rval_tree = get_rvalue_for_type(tokentype, tp);
		val = calculate_tree(rval_tree, tp.type);
	}
	symtab_create_entry(text, val, &tp, pos);
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
	struct ASTnode *left = create_ast_leaf(strdup(entry->name), A_IDENT, entry->val, current_token.pos);
	match(T_IDENT, "Identifier Expected");
	/* we can have some different type of assign token like =, += and ...
	 */
	assign_token();
	/* parse rvalue of expression and calculate it to store in value union 
	 */
	union value val = calculate_tree(parse_binary_expression(0), entry->entry_type.type);
	/* create AST leaf for our value
	 */
	struct ASTnode *rigth = create_ast_leaf("RVALUE", A_INTLIT, val, current_token.pos);
	// TODO : remove this redundant val arg
	struct ASTnode *tree = create_ast_node("ASSIGN", A_ASSIGN, val, left, rigth, current_token.pos);

	// changin symbol integer value for now
	// TODO : check assign operator type , like -= , += and ...
	//value_copy(val, entry->val);
	set_val_by_type(entry->val, val, &entry->entry_type);
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
		case T_REALLIT :
			n = create_ast_leaf(current_token.buffer, A_INTLIT, current_token.val, current_token.pos);
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
				n = create_ast_leaf(current_token.buffer, A_INTLIT, entry->val, current_token.pos);
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
		left = create_ast_node(token_copy->buffer, tokentype_to_nodetype(tokentype), current_token.val, left, right, token_copy->pos);

		tokentype = current_token.type;
		if (is_endof_binexpr())
			break;
	}
return_ast:
	return left;
}
