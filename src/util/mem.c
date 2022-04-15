/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "mem.h"

#include "basic.h"

#include <stdlib.h>
#include <assert.h>

void *ngc_malloc(size_t s)
{
	void *ptr = malloc(s);
	assert(ptr);
	return ptr;
}

void *ngc_calloc(size_t nmem, size_t s)
{
	void *ptr = calloc(nmem, s);
	assert(ptr);
	return ptr;
}

void *ngc_realloc(void *p, size_t s)
{
	void *ptr = realloc(p, s);
	assert(ptr);
	return ptr;
}

void ngc_free(void *ptr)
{
	assert(ptr);
	free(ptr);
}
