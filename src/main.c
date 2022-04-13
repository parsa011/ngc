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

void usage()
{
	print("ngc compiler Usage :\n");
}

int main(int argc, char *argv[])
{
	if (argc == 1) {
		usage();
	}
	return 0;
}
