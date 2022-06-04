/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "../ngc.h"
#include "hash_table.h"

void init_ht_table(ht_table *table)
{
	table->count = 0;
	table->capacity = 0;
}

void free_ht_table(ht_table *table)
{

}

