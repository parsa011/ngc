#include "run_test.h"

#define FILE_NAME "02_test.input"

int main()
{
	struct lexer *l = lexer_init();
	struct token toks[] = {
		{.type = T_OP_P},
		{.type = T_CL_P},
		{.type = T_CL_P},
		{.type = T_OP_CB},
		{.type = T_OP_CB},
		{.type = T_OP_CB},
		{.type = T_CL_CB},
		{.type = T_CL_CB},
		{.type = T_OBRKT},
		{.type = T_CBRKT},
		{.type = T_CARET},
		{.type = T_AND},
		{.type = T_STAR},
		{.type = T_CL_P},
		{.type = T_EXCLAM}
	};
	lexer_set_working_lexer(l);
	l->open_file(l, FILE_NAME);
	lexer_expect(l, toks, array_length(toks), FILE_NAME, false);
	return 0;
}
