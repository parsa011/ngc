/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*
*	Entry pint of ngc compiler
*/

#include "ngc.h"
#include "lexer/lexer.h"
#include <stdarg.h>
#include <stdlib.h>

void usage(char *program_name)
{
	print("ngc compiler Usage :\n");
	printf("\t %s : file\n", program_name);
	panic(NULL);
}

void panic(const char *msg,...) 
{
	if (msg) {
		char buf[256];
		va_list ap;
		va_start(ap, msg);
		vsprintf(buf, msg, ap);
		va_end(ap);
		fprintf(stderr, "%s\n", buf);
	}
	exit(0);
}

int main(int argc, char *argv[])
{
	if (argc == 1) {
		usage(argv[0]);
	}
	if (strcmp(file_extension(argv[1]), NGC_FILE_TYPE) != 0) {
		panic("Given File is not a valid 'c' file : %s", argv[1]);
	}
	return 0;
}
