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
				if (is_type_keyword(false) || is_qualifier(false)) {
					declare_variable();
				}
				break;
		}
		//struct type tp = (struct type) {.type = T_INT};
		//print_ast(parse_binary_expression(0, &tp), 0);
		if (interp_mode) {
			print_prompt();
		}
		semi();
	}
}

private struct ASTnode *declare_variable()
{
	/* check for qualifier at first of declerations
	 * default value for 'qualifer_type' is -1 , because we dont have any token with that id
	 * so in type decleration we can detect that we have a qualifier or no
	 */
	int qualifer_type = -1;
	if (is_qualifier(false)) {
		qualifer_type = current_token.type;
		next_token();
	}
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

	/* Set type qualifers with detected qualifier
	 */
	if (qualifer_type) {
		switch (qualifer_type) {
			case T_CONST :
				tp.is_const = true;
				break;
		}
	}

decl_again:

	/* here we should check for star , if current token is an star so our type is a pointer to 
	 * then we have to edit our type but for now we skip them
	 */
	if (current_token.type == T_STAR) {
		tp.is_pointer = true;
		next_token();
	} else
		tp.is_pointer = false;
	
	/* check if current token is identifier or no 
	 * it should be ident because we want to use it as variable name
	 */
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
	value val;
	if (current_token.type == T_EQUAL) {
		next_token();
		struct ASTnode *rval_tree = get_rvalue_for_type(tokentype, tp);
		val.val_type.type = tp.type;
		val = calculate_tree(rval_tree, tp.type);
		//printf("%d\n", val.intval);
	}
	/* Add parsed variable to global symbol table
	 */
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

/*
 *	it will parse statements like :
 *
 *		age = 10;
 *
 *	detect symbol , parse it value then assign value to it by considering to assign token
 *	assign token can be something like =, += and ...
 */
private struct ASTnode *parse_assign_variable()
{
	struct symtab_entry *entry = symtab_get_by_name(current_token.buffer, true);
	/* Show error if given entry is a Const variable
	 */
	if (IS_CONST_TYPE(entry->entry_type)) {
		show_lexer_error("Can't Change Const Obj Value");
		panic(NULL);
	}
	struct ASTnode *left = create_ast_leaf(strdup(entry->name), A_IDENT, entry->val, &entry->entry_type, current_token.pos);
	match(T_IDENT, "Identifier Expected");

	/* we can have some different type of assign token like =, += and ...
	 */
	int operation_type = current_token.type;
	assign_token();

	/* parse rvalue of expression and calculate it to store in value union 
	 */
	value val = calculate_tree(parse_binary_expression(0, &entry->entry_type), entry->entry_type.type);
	val.val_type.type = entry->entry_type.type;

	/* create AST leaf for our value
	 */
	struct ASTnode *rigth = create_ast_leaf("RVALUE", A_CONST, val, &entry->entry_type, current_token.pos);
	/* Final tree
	 */
	struct ASTnode *tree = create_ast_node("ASSIGN", A_ASSIGN, val, &entry->entry_type, left, rigth, current_token.pos);

	// TODO : check assign operator type , like -= , += and ...
	set_val_by_type(&entry->val, &val, operation_type);
	return tree;
}

/*
 *	get value for a type , for example for int literals and ...
 *
 *		int age = expr;
 *
 *		char ch = ident | 'c';
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
		case T_LONG :
		case T_DOUBLE :
		case T_FLOAT :
			res = parse_binary_expression(0, &info);
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

/*
 * return a leaf that contains a value corresponding to given type .
 * for example if given type kind is string literal , so current token should be
 * a strin literal , no numerical value
 */
private struct ASTnode *primary_factor(int ptp, struct type *tp)
{
	/* Do not check types if current token is open parenthesis
	 */
	if (!check_literal_and_type(&current_token, tp) && current_token.type != T_OP_P) {
		// TODO : enhance bug reporting
		show_lexer_error("Value And Type Are Not Match");
		panic(NULL);
	}
	struct ASTnode *n;
	switch (current_token.type) {

		case T_INTLIT :
		case T_LONGLIT :
		case T_REALLIT :
			n = create_ast_leaf(current_token.buffer, A_CONST, current_token.val, tp, current_token.pos);
			next_token();
			return n;

		case T_OP_P :
			next_token();
			n = parse_binary_expression(0, tp);
			match(T_CL_P, "Unclosed Parenthesis");
			return n;

		case T_IDENT :
			{
				struct symtab_entry *entry = symtab_get_by_name(current_token.buffer, true);
				next_token();
				n = create_ast_leaf(current_token.buffer, A_CONST, entry->val, tp, current_token.pos);
				return n;
			}

		default :
			show_lexer_error("Bad Token");
			panic(NULL);
			break;

	}
	return NULL;
}

private struct ASTnode *parse_binary_expression(int ptp, struct type *tp)
{
	struct ASTnode *right, *left;
	/* get numerical part of expression
	 * here, our token should be a valid numerical token, it can a be a symbol that contains a numeric value
	 * or it can be constant
	 */
	left = primary_factor(ptp, tp);
	int tokentype = current_token.type;
	/* save type of current token , it can be open parenthesis or a operation token like + , - and ...
	 */
	if (is_endof_binexpr())
		goto return_ast;
	struct token *token_copy;
	while (token_precedence(tokentype) > ptp) {
		/* take a copy of current token , we need position and buffer of it for making ASTnode
		 */
		token_copy = token_duplicate(&current_token);
		next_token();
		/* parse continuationi of expression , it will just primary(number) if next operation token precedence is 
		 * less than current operation token precedence
		 */
		right = parse_binary_expression(token_precedence(tokentype), tp);
		/* join past trees with new tree from 'right'
		 */
		left = create_ast_node(token_copy->buffer, tokentype_to_nodetype(tokentype), current_token.val, tp, left, right, token_copy->pos);
		tokentype = current_token.type;
		/* check if we can get out of this loop, chekcs if current token is like semi or comma or ...
		 */
		if (is_endof_binexpr())
			break;
	}
return_ast:
	return left;
}
