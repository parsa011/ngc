#include "run_test.h"

#define FILE_NAME "01_test_operators.input"

int main()
{
	struct lexer *l = lexer_init();
	// ++ -- - / -= ++
	struct token toks[] = {
		{.type = T_INC},
		{.type = T_DEC},
		{.type = T_DASH},
		{.type = T_SLASH},
		{.type = T_DECEQUAL},
		{.type = T_INC}
	};
	l->open_file(l, FILE_NAME);
	lexer_set_working_lexer(l);
	lexer_expect(l, toks, array_length(toks), FILE_NAME, false);
	return 0;
}
