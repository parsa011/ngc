#ifndef _FILE_UTIL_H
# define _FILE_UTIL_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "basic.h"

char *basename(char *);

char *file_extension(char *);

bool file_exist(char *);

#endif
