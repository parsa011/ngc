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
n */
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
				return TOKEN_AUTO;
			break;

		case 'b' :
			if (STR_EQUAL(text, "break"))
				return TOKEN_BREAK;
			break;

		case 'c' :
			if (STR_EQUAL(text, "char"))
				return TOKEN_CHAR;
			else if (STR_EQUAL(text, "case"))
				return TOKEN_CASE;
			else if (STR_EQUAL(text, "continue"))
				return TOKEN_CONTINUE;
			else if (STR_EQUAL(text, "const"))
				return TOKEN_CONST;
			break;

		case 'd' :
			if (STR_EQUAL(text, "do"))
				return TOKEN_DO;
			else if (STR_EQUAL(text, "default"))
				return TOKEN_DEFAULT;
			else if (STR_EQUAL(text, "double"))
				return TOKEN_DOUBLE;
			break;

		case 'e' :
			if (STR_EQUAL(text, "enum"))
				return TOKEN_ENUM;
			else if (STR_EQUAL(text, "extern"))
				return TOKEN_EXTERN;
			else if (STR_EQUAL(text, "else"))
				return TOKEN_ELSE;
			break;

		case 'f' :
			if (STR_EQUAL(text, "for"))
				return TOKEN_FOR;
			else if (STR_EQUAL(text, "float"))
				return TOKEN_FLOAT;
			break;

		case 'g' :
			if (STR_EQUAL(text, "goto"))
				return TOKEN_GOTO;
		
		case 'l' :
			if (STR_EQUAL(text, "label"))
				return TOKEN_LABEL;
			else if (STR_EQUAL(text, "long"))
				return TOKEN_LONG;
			break;

		case 'r' :
			if (STR_EQUAL(text, "return"))
				return TOKEN_RETURN;
			else if (STR_EQUAL(text, "register"))
				return TOKEN_REGISTER;
			else if (STR_EQUAL(text, "restrict"));
				return TOKEN_RESTRICT;
			break;

		case 's' :
			if (STR_EQUAL(text, "sizeof"))
				return TOKEN_SIZEOF;
			else if (STR_EQUAL(text, "signed"))
				return TOKEN_SIGNED;
			else if (STR_EQUAL(text, "static"))
				return TOKEN_STATIC;
			else if (STR_EQUAL(text, "switch"))
				return TOKEN_SWITCH;
			break;

		case 't' :
			if (STR_EQUAL(text, "typedef"))
				return TOKEN_TYPEDEF;
			break;

		case 'i' :
			if (STR_EQUAL(text, "int"))
				return TOKEN_INT;
			else if (STR_EQUAL(text, "if"))
				return TOKEN_IF;
			break;

#if NGC_DEBUG
		case 'p':
			if (STR_EQUAL(text, "print"))
				return TOKEN_PRINT;
			break;
#endif			

		case 'v' :
			if (STR_EQUAL(text, "volatile"))
				return TOKEN_VOLATILE;
			else if (STR_EQUAL(text, "void"))
				return TOKEN_VOID;
			break;

		case 'u' :
			if (STR_EQUAL(text, "union"))
				return TOKEN_UNION;
			else if (STR_EQUAL(text, "unsigned"))
				return TOKEN_UNSIGNED;
			break;

		case 'w' :
			if (STR_EQUAL(text, "while"))
				return TOKEN_WHILE;
			break;

	}
	return TOKEN_IDENT;
}

public void print_token(token *t)
{
	printf("%s --> %s%s%s (%d)", get_token_str(t->type), COLORCYAN, t->buffer, COLORDEFAULT, t->bufp);
	switch (t->type) {

		case TOKEN_INTLIT :
			printf(" --> Value : %s%d%s" , COLORUNDLINE, VALUE_AS_INT(t->val), COLORDEFAULT);
			break;

		case TOKEN_LONGLIT :
			printf(" --> Value : %s%ld%s" , COLORUNDLINE, VALUE_AS_LONG(t->val), COLORDEFAULT);
			break;
		
		case TOKEN_STRLIT :
		case TOKEN_CHARLIT :
			printf(" --> Value : %s%s%s", COLORUNDLINE, VALUE_AS_STRING(t->val)->value, COLORDEFAULT);
			break;

		case TOKEN_DOUBLELIT :
		case TOKEN_FLOATLIT :
			printf(" --> Value : %s%f%s", COLORUNDLINE, t->type == TOKEN_DOUBLELIT ? VALUE_AS_DOUBLE(t->val) : VALUE_AS_FLOAT(t->val), COLORDEFAULT);
			break;

	}
	printf (" (%d:%d)", t->pos.line, t->pos.col);
	putchar('\n');
}

public int token_precedence(token_type type)
{
	switch (type) {

		case TOKEN_ANDAND :
		case TOKEN_PIPEPIPE :
			return 2;

		case TOKEN_GT :
		case TOKEN_LT :
		case TOKEN_ISEQUAL :
		case TOKEN_NOTEQUAL :
		case TOKEN_LOWEQ :
		case TOKEN_GREAEQ :
			return 4;

		case TOKEN_PLUS :
		case TOKEN_DASH :
			return 5;

		case TOKEN_STAR :
		case TOKEN_SLASH :
		case TOKEN_PERCENT :
		case TOKEN_AND :
		case TOKEN_EXCLAM :
			return 6;
	}

	return -1;
}

public bool is_type_token(token_type type)
{
	switch (type) {
		case TOKEN_INT :
		case TOKEN_LONG :
		case TOKEN_CHAR :
		case TOKEN_DOUBLE :
		case TOKEN_FLOAT :
			return true;
	}
	return false;
}

public bool is_assign_token(token_type type)
{
	switch (type) {
		case TOKEN_EQUAL :
		case TOKEN_INCEQUAL :		// +=
		case TOKEN_DECEQUAL :		// -=
		case TOKEN_MUEQUAL :		// *=
		case TOKEN_MODEQUAL :		// %=
		case TOKEN_SHLEQUAL :		// <<=
		case TOKEN_SHREQUAL :		// >>=
		case TOKEN_DIVEQUAL :		// /=
		case TOKEN_NOTEQUAL :		// !=
		case TOKEN_ANDEQUAL :		// &=
		case TOKEN_OREQUAL :		// |=
		case TOKEN_XOREQUAL :		// ^=
			return true;
	}
	return false;
}
