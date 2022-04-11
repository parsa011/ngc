#! /bin/bash

paths=$(find . -name "Makefile")

SAVEIFS=$IFS   # Save current IFS (Internal Field Separator)
IFS=$'\n'      # Change IFS to newline char
names=($paths) # split the `names` string into an array by the same name
IFS=$SAVEIFS   # Restore original IFS

for (( i=0; i<${#names[@]}; i++ ))
do
	echo "Adding : ${names[$i]}" 
	git add ${names[$i]} 
done
