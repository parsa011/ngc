/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "token.h"

/*
 *	TODO : panic if id was out or token_type_str array range
 */
public char *get_token_str(int id)
{
	return token_type_str[id];
}

public token *token_init(token_type type)
{
	token *t = ngc_malloc(sizeof(token));
	t->type = type;
	return t;
}

public token *token_duplicate(token *n)
{
	token *t = ngc_malloc(sizeof(token));
	t->type = n->type;
	t->bufp = n->bufp;
	memcpy(t->buffer, n->buffer, n->bufp);
	pos_copy(n->pos, t->pos);
	return t;
}

public void token_free(token *p)
{
	ngc_free(p);
}

public token_type guess_text_type(char *text)
{
	// TODO : implement this function
	switch (*text) {

		case 'a' :
			if (STR_EQUAL(text, "auto"))
				return T_AUTO;
			break;

		case 'b' :
			if (STR_EQUAL(text, "break"))
				return T_BREAK;
			break;

		case 'c' :
			if (STR_EQUAL(text, "char"))
				return T_CHAR;
			else if (STR_EQUAL(text, "case"))
				return T_CASE;
			else if (STR_EQUAL(text, "continue"))
				return T_CONTINUE;
			else if (STR_EQUAL(text, "const"))
				return T_CONST;
			break;

		case 'd' :
			if (STR_EQUAL(text, "do"))
				return T_DO;
			else if (STR_EQUAL(text, "default"))
				return T_DEFAULT;
			else if (STR_EQUAL(text, "double"))
				return T_DOUBLE;
			break;

		case 'e' :
			if (STR_EQUAL(text, "enum"))
				return T_ENUM;
			else if (STR_EQUAL(text, "extern"))
				return T_EXTERN;
			else if (STR_EQUAL(text, "else"))
				return T_ELSE;
			break;

		case 'f' :
			if (STR_EQUAL(text, "for"))
				return T_FOR;
			else if (STR_EQUAL(text, "float"))
				return T_FLOAT;
			break;

		case 'g' :
			if (STR_EQUAL(text, "goto"))
				return T_GOTO;
		
		case 'l' :
			if (STR_EQUAL(text, "label"))
				return T_LABEL;
			else if (STR_EQUAL(text, "long"))
				return T_LONG;
			break;

		case 'r' :
			if (STR_EQUAL(text, "return"))
				return T_RETURN;
			else if (STR_EQUAL(text, "register"))
				return T_REGISTER;
			else if (STR_EQUAL(text, "restrict"));
				return T_RESTRICT;
			break;

		case 's' :
			if (STR_EQUAL(text, "sizeof"))
				return T_SIZEOF;
			else if (STR_EQUAL(text, "signed"))
				return T_SIGNED;
			else if (STR_EQUAL(text, "static"))
				return T_STATIC;
			else if (STR_EQUAL(text, "switch"))
				return T_SWITCH;
			break;

		case 't' :
			if (STR_EQUAL(text, "typedef"))
				return T_TYPEDEF;
			break;

		case 'i' :
			if (STR_EQUAL(text, "int"))
				return T_INT;
			else if (STR_EQUAL(text, "if"))
				return T_IF;
			break;

		case 'v' :
			if (STR_EQUAL(text, "volatile"))
				return T_VOLATILE;
			else if (STR_EQUAL(text, "void"))
				return T_VOID;
			break;

		case 'u' :
			if (STR_EQUAL(text, "union"))
				return T_UNION;
			else if (STR_EQUAL(text, "unsigned"))
				return T_UNSIGNED;
			break;

		case 'w' :
			if (STR_EQUAL(text, "while"))
				return T_WHILE;
			break;

	}
	return T_IDENT;
}

public void print_token(token *t)
{
	printf("%s --> %s%s%s (%d)", get_token_str(t->type), COLORCYAN, t->buffer, COLORDEFAULT, t->bufp);
	switch (t->type) {

		case T_INTLIT :
			printf(" --> Value : %s%d%s" , COLORUNDLINE, VALUE_AS_INT(t->val), COLORDEFAULT);
			break;

		case T_LONGLIT :
			printf(" --> Value : %s%ld%s" , COLORUNDLINE, VALUE_AS_LONG(t->val), COLORDEFAULT);
			break;
		
		case T_STRLIT :
		case T_CHARLIT :
			printf(" --> Value : %s%s%s", COLORUNDLINE, VALUE_AS_STRING(t->val)->value, COLORDEFAULT);
			break;

		case T_DOUBLELIT :
		case T_FLOATLIT :
			printf(" --> Value : %s%f%s", COLORUNDLINE, t->type == T_DOUBLELIT ? VALUE_AS_DOUBLE(t->val) : VALUE_AS_FLOAT(t->val), COLORDEFAULT);
			break;

	}
	printf (" (%d:%d)", t->pos.line, t->pos.col);
	putchar('\n');
}

public int token_precedence(token_type type)
{
	switch (type) {

		case T_GT :
		case T_LT :
		case T_ISEQUAL :
		case T_LOWEQ :
		case T_GREAEQ :
			return 4;

		case T_PLUS :
		case T_DASH :
			return 5;

		case T_STAR :
		case T_SLASH :
		case T_PERCENT :
		case T_AND :
		case T_EXCLAM :
			return 6;
	}

	return -1;
}

public bool is_type_token(token_type type)
{
	switch (type) {
		case T_INT :
		case T_LONG :
		case T_CHAR :
		case T_DOUBLE :
		case T_FLOAT :
			return true;
	}
	return false;
}

public bool is_assign_token(token_type type)
{
	switch (type) {
		case T_EQUAL :
		case T_INCEQUAL :		// +=
		case T_DECEQUAL :		// -=
		case T_MUEQUAL :		// *=
		case T_MODEQUAL :		// %=
		case T_SHLEQUAL :		// <<=
		case T_SHREQUAL :		// >>=
		case T_DIVEQUAL :		// /=
		case T_NOTEQUAL :		// !=
		case T_ANDEQUAL :		// &=
		case T_OREQUAL :		// |=
		case T_XOREQUAL :		// ^=
			return true;
	}
	return false;
}
