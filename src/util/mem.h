#ifndef _MEM_H
# define _MEM_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*
*	Memory-bound Utility function
*/

#include <stddef.h>

/*
 *	@brief : malloc memory with given size
 */
void *ngc_malloc(size_t);

/*
 *	@brief : calloc, panic when error happened
 */
void *ngc_calloc(size_t, size_t);

/*
 *	@brief : relloc given pointer with new size
 */
void *ngc_realloc(void *, size_t);

/*
 *	@brief : just free, no more
 */
void ngc_free(void *);

#endif
