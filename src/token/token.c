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

public struct token *token_init(token_type type)
{
	struct token *t = ngc_malloc(sizeof(struct token));
	t->type = type;
	return t;
}

public struct token *token_duplicate(struct token *n)
{
	struct token *t = ngc_malloc(sizeof(struct token));
	t->type = n->type;
	t->pos.line = n->pos.line;
	t->pos.col = n->pos.col;
	return t;
}

public void token_free(struct token *p)
{
	ngc_free(p);
}

public token_type guess_text_type(char *text)
{
	// TODO : implement this function
	switch (*text) {

		case 'a' :
			if (!strcmp(text, "auto"))
				return T_AUTO;
			break;

		case 'b' :
			if (!strcmp(text, "break"))
				return T_BREAK;
			break;

		case 'c' :
			if (!strcmp(text, "char"))
				return T_CHAR;
			else if (!strcmp(text, "case"))
				return T_CASE;
			else if (!strcmp(text, "continue"))
				return T_CONTINUE;
			else if (!strcmp(text, "const"))
				return T_CONST;
			break;

		case 'd' :
			if (!strcmp(text, "do"))
				return T_DO;
			else if (!strcmp(text, "default"))
				return T_DEFAULT;
			else if (!strcmp(text, "double"))
				return T_DOUBLE;
			break;

		case 'e' :
			if (!strcmp(text, "enum"))
				return T_ENUM;
			else if (!strcmp(text, "extern"))
				return T_EXTERN;
			else if (!strcmp(text, "else"))
				return T_ELSE;
			break;

		case 'f' :
			if (!strcmp(text, "for"))
				return T_FOR;
			else if (!strcmp(text, "float"))
				return T_FLOAT;
			break;

		case 'g' :
			if (!strcmp(text, "goto"))
				return T_GOTO;
		
		case 'l' :
			if (!strcmp(text, "label"))
				return T_LABEL;
			else if (!strcmp(text, "long"))
				return T_LONG;
			break;

		case 'r' :
			if (!strcmp(text, "return"))
				return T_RETURN;
			else if (!strcmp(text, "register"))
				return T_REGISTER;
			else if (!strcmp(text, "restrict"));
				return T_RESTRICT;
			break;

		case 's' :
			if (!strcmp(text, "sizeof"))
				return T_SIZEOF;
			else if (!strcmp(text, "signed"))
				return T_SIGNED;
			else if (!strcmp(text, "static"))
				return T_STATIC;
			else if (!strcmp(text, "switch"))
				return T_SWITCH;
			break;

		case 't' :
			if (!strcmp(text, "typedef"))
				return T_TYPEDEF;
			break;

		case 'i' :
			if (!strcmp(text, "int"))
				return T_INT;
			else if (!strcmp(text, "if"))
				return T_IF;
			break;

		case 'v' :
			if (!strcmp(text, "volatile"))
				return T_VOLATILE;
			else if (!strcmp(text, "void"))
				return T_VOID;
			break;

		case 'u' :
			if (!strcmp(text, "union"))
				return T_UNION;
			else if (!strcmp(text, "unsigned"))
				return T_UNSIGNED;
			break;

		case 'w' :
			if (!strcmp(text, "while"))
				return T_WHILE;
			break;

	}
	return T_IDENT;
}

public void print_token(struct token *t)
{
	printf("%s --> %s%s%s (%d)", get_token_str(t->type), COLORCYAN, t->buffer, COLORDEFAULT, t->bufp);
	switch (t->type) {

		case T_INTLIT :
			printf(" --> Value : %s%ld%s" , COLORUNDLINE, t->longval, COLORDEFAULT);
			break;
		
		case T_STRLIT :
		case T_CHARLIT :
			printf(" --> Value : %s%s%s", COLORUNDLINE, t->str->value, COLORDEFAULT);
			break;

		case T_REALLIT :
			printf(" --> Value : %s%f%s", COLORUNDLINE, t->real, COLORDEFAULT);
			break;

	}
	putchar('\n');
}
