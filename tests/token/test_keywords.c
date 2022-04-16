#include "../../src/token/token.h"
#include <string.h>

struct expect {
	int type;
	char *text;
};

void run_test()
{
	struct expect list[] = {
		{T_DO, "do"},
		{T_WHILE, "while"},
		{T_FOR, "for"},
		{T_IF, "if"},
		{T_ELSE, "else"},
		{T_INT, "int"},
		{T_ENUM, "enum"},
		{T_IDENT, "Int"},
		{T_DOUBLE, "double"}
	};
	int t = -1;
	int error = 0;
	for (int i = 0; i < sizeof(list) / sizeof(list[0]); i++) {
		t = guess_text_type(list[i].text);
		if (t != list[i].type) {
			error++;
			printf("invalid text type : <'%s'> -----> %d (%s)\n", list[i].text, t, get_token_str(t));
		}
	}
	printf("%d error occured when testing get text type\n", error);
}

int main(int argc, char **argv)
{
	run_test();
	return 0;
}
