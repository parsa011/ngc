/*
 *	work with string single file library
 *	parsa mahmoudy 2022
 */
#ifndef _PROSING_H
#define _PROSING_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define null_str ((string){ NULL, 0 })

typedef struct string_t {
	char *value;
	int len;
} string;

extern void prosing_string_free(string *);

/*
 *	make string value null and set len to 0
 */
extern void prosing_string_reset(string *);

/*
 *	this is main routine for create new string
 *	we will caluculate value len
 */
extern string *prosing_string_init(char *value);

/*
 *	allocate and return duplicate of given string
 */
extern char *prosing_string_dup(char *);

/*
 *	reverse string and save it into given string
 */
extern char *prosing_string_reverse(string *);

/*
 *	check if given check exist in string
 */
extern bool prosing_string_contains_char(string *, char);
/*
 *	return how many time given char repeated in string
 */
extern int prosing_string_ncontains_char(string *, char);

/*
 *	check if given string exist in string
 */
extern bool prosing_string_contains_string(string *, char *);
/*
 *	return how many time given string repeated in string
 */
extern int prosing_string_ncontains_string(string *, char *);

/*
 *	functions declerations, work with char
 *  because string struct have len prop and we
 *  dont need to call function to calculate string
 *  len
 */
extern int prosing_string_length(char *);

/*
 *	compare two string , it works like strcpm
 */
extern int prosing_string_compare(string *, char *);
extern int prosing_string_ncompare(string *, char *, int);

extern bool prosing_string_endwith(string *, char *);

/*
 *	append t to last of str
 */
extern char *prosing_string_append(string *, char *);
extern char *prosing_string_append_char(string *, char);

/*
 *	insert char at specified location in string
 */
extern char *prosing_string_insert_char(string *, char, int);

/*
 *	insert string into string
 */
extern char *prosing_string_insert_string(string *, char *, int);

/*
 *	substing and save new string in given str
 */
extern char *prosing_string_substring(string *, int, int);

/*
 *	remove character at given position from string
 */
extern char *prosing_string_remove(string *, int);
extern char *prosing_string_remove_range(string *, int, int);

/*
 *	replace old with new in given string and return string
 */
extern char *prosing_string_replace(string *, char *, char *);

/*
 *	split given stirng by another string
 */
extern char **prosing_string_split(string *, char *);

/*
 *	make string and join args elements
 */
extern string *prosing_string_join(char **args, char *);

#endif
