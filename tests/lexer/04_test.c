#include "run_test.h"

#define FILE_NAME "04_test.input"

int main()
{
	struct lexer *l = lexer_init();
	// ++ -- - / -= ++
	struct token toks[] = {
		{.type = T_INT},
		{.type = T_IDENT},
		{.type = T_OP_P},
		{.type = T_INT},
		{.type = T_IDENT},
		{.type = T_COMMA},
		{.type = T_CHAR},
		{.type = T_STAR},
		{.type = T_IDENT},
		{.type = T_OBRKT},
		{.type = T_CBRKT},
		{.type = T_CL_P},
		{.type = T_OP_CB},
		{.type = T_INT},
		{.type = T_IDENT},
		{.type = T_SEMI},
		{.type = T_SWITCH},
		{.type = T_OP_P},
		{.type = T_IDENT},
		{.type = T_CL_P},
		{.type = T_OP_CB},
		{.type = T_CASE},
		{.type = T_CHARLIT},
		{.type = T_ELLIPSIS},
		{.type = T_CASE},
		{.type = T_CHARLIT},
		{.type = T_COLON},
		{.type = T_BREAK},
		{.type = T_SEMI},
		{.type = T_CL_CB},
		{.type = T_RETURN},
		{.type = T_INTLIT},
		{.type = T_SEMI},
		{.type = T_CL_CB}
	};
	l->open_file(l, FILE_NAME);
	lexer_set_working_lexer(l);
	lexer_expect(l, toks, array_length(toks), FILE_NAME, false);
	return 0;
}
