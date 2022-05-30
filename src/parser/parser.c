/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser.h"

public ASTnode *compile(lexer *l)
{
	select_lexer(l);
	if (interp_mode) {
		print_prompt();
	}
	next_token();
	ASTnode *n = statements(n);
	return n;
}

private ASTnode *statements(ASTnode *n)
{
    ASTnode *ast = NULL;
	while (!is_eof()) {
		switch (current_token.type) {

			case T_IF :
				parse_if_statement();
				break;

			case T_IDENT :
				parse_assign_variable();
				break;

			default :
				if (is_type_keyword(false) || is_qualifier(false)) {
					declare_variable();
				}
				break;
		}
		if (interp_mode) {
			print_prompt();
		}
		semi();
	}
	return ast;
}

private ASTnode *declare_variable()
{
	/* check for qualifier at first of declerations
	 * we use of a temp 'type' struct to hold qualifiers like 'const' and  ...
	 * then we copy it to the finall 'type'
	 */
	type qualifiers;
	qualifiers.is_const = qualifiers.is_unsigned = false;
	while (is_qualifier(false)) {
		if (current_token.type == T_CONST) {
			if (qualifiers.is_const) {
			show_lexer_error("Variable Is Constant Already");
				panic(NULL);
			}
			qualifiers.is_const = true;
		} else if (current_token.type == T_UNSIGNED) {
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
	if (current_token.type == T_EQUAL) {
		next_token();
		ASTnode *rval_tree = get_rvalue_for_type(tp);
		//val.type = tp.type;
		val = calculate_tree(rval_tree, tp.type);
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
private ASTnode *parse_assign_variable()
{
	symtab_entry *entry = symtab_get_by_name(current_token.buffer, true);
	/* Show error if given entry is a Const variable
	 */
	if (IS_CONST_TYPE(entry->entry_type)) {
		show_lexer_error("Can't Change Const Value");
		panic(NULL);
	}
	ASTnode *left = create_ast_leaf(strdup(entry->name), A_IDENT, entry->val, current_token.pos);
	match(T_IDENT, "Identifier Expected");

	/* we can have some different type of assign token like =, += and ...
	 */
	int operation_type = current_token.type;
	assign_token();

	/* parse rvalue of expression and calculate it to store in value union 
	 */
	value val = calculate_tree(parse_binary_expression(0, &entry->entry_type), entry->entry_type.type);

	/* create AST leaf for our value
	 */
	ASTnode *rigth = create_ast_leaf("RVALUE", A_CONST, val, current_token.pos);
	/* Build Final tree
	 */
	ASTnode *tree = create_ast_node("ASSIGN", A_ASSIGN, val, left, rigth, current_token.pos);

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
private ASTnode *get_rvalue_for_type(type tp)
{
	ASTnode *res = NULL;
	//switch (tp.type) {

		//case TYPE_INT :
		//case TYPE_LONG :
		//case TYPE_DOUBLE :
		//case TYPE_FLOAT :
			res = parse_binary_expression(0, &tp);
		// 	break;

	//	case TYPE_CHAR :
	//		if (tp.is_pointer)
	//			res = parse_str_literal();
	//		break;

	//}
	return res;
}

private ASTnode *parse_str_literal()
{
    print_token(&current_token);
	ASTnode *n = create_ast_leaf(current_token.buffer, A_STR, current_token.val, current_token.pos);
	next_token();
	return n;
}

/*
 * return a leaf that contains a value corresponding to given type .
 * for example if given type kind is string literal , so current token should be
 * a strin literal , no numerical value
 */
private ASTnode *primary_factor(int ptp, type *tp)
{
	/* Do not check types if current token is open parenthesis
	 */
	if (!check_literal_and_type(&current_token, tp) && current_token.type != T_OP_P) {
		// TODO : enhance bug reporting
		show_lexer_error("Value And Type Are Not Match");
		panic(NULL);
	}

	ASTnode *n;
	switch (current_token.type) {

		case T_INTLIT :
		case T_LONGLIT :
		case T_DOUBLELIT :
		case T_FLOATLIT :
        case T_CHARLIT :
        case T_STRLIT :
            {
                ASTnode_type tp;
                if (current_token.type == T_CHARLIT || current_token.type == T_STRLIT)
                    tp = A_STR;
                else
                    tp = A_CONST;
    			n = create_ast_leaf(current_token.buffer, tp, current_token.val, current_token.pos);
    			next_token();
    			return n;
        	}

		case T_OP_P :
			next_token();
			n = parse_binary_expression(0, tp);
			match(T_CL_P, "Unclosed Parenthesis");
			return n;

		case T_IDENT :
			{
				symtab_entry *entry = symtab_get_by_name(current_token.buffer, true);
				ASTnode_type tp;
				if (entry->entry_type.type == TYPE_CHAR || entry->entry_type.type == TYPE_STRING)
					tp = A_STR;
				else
					tp = A_CONST;
				n = create_ast_leaf(current_token.buffer, tp, entry->val, current_token.pos);
				next_token();
				return n;
			}

		default :
			show_lexer_error("Bad Token");
			panic(NULL);
			break;

	}
	return NULL;
}

private ASTnode *parse_binary_expression(int ptp, type *tp)
{
	ASTnode *right, *left;
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
	token *token_copy;
	while (token_precedence(tokentype) > ptp) {
		/* take a copy of current token , we need position and buffer of it for making ASTnode
		 */
		token_copy = token_duplicate(&current_token);
		next_token();
		/* parse continuation of expression , it will parse just primary(number) if next operation token precedence is 
		 * less than current operation token precedence
		 */
		right = parse_binary_expression(token_precedence(tokentype), tp);
		/* join past trees with new tree from 'right'
		 */
		left = create_ast_node(token_copy->buffer, tokentype_to_nodetype(tokentype), current_token.val, left, right, token_copy->pos);
		tokentype = current_token.type;
		/* check if we can get out of this loop, chekcs if current token is like semi or comma or ...
		 */
		if (is_endof_binexpr())
			break;
	}
return_ast:
	return left;
}

private ASTnode *parse_if_statement()
{
	ASTnode *condition_tree, *if_tree, *else_tree;
	return NULL;
}
