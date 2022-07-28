/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "decleration.h"
#include "expression.h"

public ASTnode *parse_variable_decleration()
{
	/* check for qualifier at first of declerations
	 * we use of a temp 'type' struct to hold qualifiers like 'const' and  ...
	 * then we copy it to the finall 'type'
	 */
	type qualifiers;
	qualifiers.is_const = qualifiers.is_unsigned = false;
	while (is_qualifier(false)) {
		if (current_token.type == TOKEN_CONST) {
			if (qualifiers.is_const) {
				show_lexer_error("Variable Is Constant Already");
				panic(NULL);
			}
			qualifiers.is_const = true;
		} else if (current_token.type == TOKEN_UNSIGNED) {
			if (qualifiers.is_unsigned) {
				show_lexer_error("Variable Is Unsigned Already");
				panic(NULL);
			}
			qualifiers.is_unsigned = true;
		}
		next_token();
	}

	/* save type of current token ('type' token type)
	 */
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
	type tp;
	type_copy(((type *)&qualifiers), ((type *)&tp));
	/* set type for 'type' here , because if we set that before type_copy we will lose our type-specifier */
	tp.type = token_type_to_type_kind(tokentype);
decl_again:

	/* here we should check for star , if current token is an star so our type is a pointer to 
	 * then we have to edit our type but for now we skip them
	 */
	if (current_token.type == TOKEN_STAR) {
		tp.is_pointer = true;
		next_token();
	} else
		tp.is_pointer = false;
	
	/* check if current token is identifier or no 
	 * it should be ident because we want to use it as variable name
	 */
	if (current_token.type != TOKEN_IDENT) {
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
	value val;
	/* This is important , because when we are declaring many variables in one line, those variable that
	 * dont have any right value will take the last rvalue ,  like this :
	 *
	 *		int my_age = 18, your_age;
	 *
	 *	here your_age should be 0 , but it will be 18 , so we have to reset the value
	 */
	val.intval = 0;
	/*
	 * check if current token is assign token or no 
	 * if it is , so we gonna parse right value
	 */
	if (current_token.type == TOKEN_EQUAL) {
		next_token();
		ASTnode *rval_tree = parse_expression(0);
		val = calculate_tree(rval_tree, tp);
	}
	/* Add parsed variable to global symbol table
	 */
	symtab_create_entry(text, val, &tp, pos);
	if (current_token.type == TOKEN_COMMA) {
		/*
		 * int age = 10, count;
		 *             ^
		 * we are here and we want to declare another variable again
		 */
		next_token();
		goto decl_again;
	}
	free(text);
	return create_ast_node("Decleration", A_DECLER, val, NULL, NULL, current_lexer->pos);
}
