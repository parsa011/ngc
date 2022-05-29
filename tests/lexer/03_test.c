#include "run_test.h"

#define FILE_NAME "03_test.input"

int main()
{
	lexer *l = lexer_init();
	// ++ -- - / -= ++
	token toks[] = {
		{.type = T_SHLEQUAL},
		{.type = T_SHIFT_R},
		{.type = T_QUES},
		{.type = T_SHLEQUAL},
		{.type = T_DASH},
		{.type = T_DECEQUAL},
		{.type = T_INCEQUAL},
		{.type = T_MODEQUAL},
		{.type = T_EXCLAM},
		{.type = T_TILDE},
		{.type = T_PIPEPIPE},
		{.type = T_OREQUAL}
	};
	l->open_file(l, FILE_NAME);
	lexer_set_working_lexer(l);
	lexer_expect(l, toks, array_length(toks), FILE_NAME, false);
	return 0;
}
