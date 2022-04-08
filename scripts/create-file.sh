#!/bin/bash

is_header_file=0

license="/*\n\
*	ngc programming language\n\
*	Copyright\n\
*		(C) 2022 Parsa Mahmoudy Sahebi\n\
*\n\
*	This file is part of ngc languge (new generation c)\n\
*/\n"

if [ -e $1 ]; then
	echo "File $1 already exists!"
else

	if [ "${1: -2}" == ".h" ] 
	then
		is_header_file=1
		printf "#ifndef _" >> "$1"
		printf '%s' "$(basename ${1})" | awk '{ print toupper($0) }' | tr . _  >> "$1"
		printf "# define _" >> "$1"
		printf '%s' "$(basename ${1})" | awk '{ print toupper($0) }' | tr . _  >> "$1"
	fi

	echo -e "$license" >> "$1"

	if [[ $is_header_file == 1 ]] 
	then
		printf "#endif" >> "$1"
	fi
fi
