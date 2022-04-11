#!/bin/bash

# This script check If we have some header file or no
# define macro with value '1' for every header file that exist on
# runner machine

# Our config file name that we want to write output into it
config_file=config.h
# Just a temp file to pass into gcc
temp_file=temp.h

rm -f $config_file

# Define Every header file that you want to check
# first should be header name to use in include, second should be Title that will
#  be inserted into config_file
declare -A headers=( ["stdbool.h"]="BOOL" ["assert.h"]="ASSERT")

for header in "${!headers[@]}"; do 
	header_name=${headers[$header]}
	echo "#include <$header>" > $temp_file

	if gcc -E temp.h > /dev/null 2>&1 
	then
		echo "have $header... yes!"
		echo "#define HAVE_$header_name 1" >> $config_file
	else
		echo "have $header... no!"
		echo "#define HAVE_$header_name 0" >> $config_file
	fi
done

rm -f $temp_file
