/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "file_util.h"
#include <string.h>
#include <unistd.h>

char *basename(char *s)
{
	int len = strlen(s);
	char *end_p = s + len - 1;
	while (end_p != s && *end_p != '/') {
		end_p--;
	}
	return ++end_p;
}

char *file_extension(char *f)
{
	int len = strlen(f);
	char *end_p = f + len - 1;
	while (end_p != f && *end_p != '.') {
		end_p--;
	}
	return ++end_p;
}

bool file_exist(char *path)
{
	return access(path, F_OK) == 0;
}
