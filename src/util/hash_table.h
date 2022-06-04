#ifndef _HASH_TABLE_H
# define _HASH_TABLE_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*
*	Implement Hash Table
*/

typedef struct ht_entry_t ht_entry;
typedef struct ht_table_t ht_table;

/*
 * Hash table entry
 */
struct ht_entry_t{
	ht_entry *next;
	/* Do not use this fields Directly
	 */
	size_t _index;
	ht_table *_table;
};

/*
 *	Hash Table struct that hold entries
 */
struct ht_table_t {
	int capacity;
	int count;
	ht_entry *entries;
};

/*
 *	@brief : Give pointer of a table then initialize it
 *	Every table that wanted to be used should be initialized first with this funtion
 */
void ht_init_table(ht_table *table);

/*
 *	@brief : Free Given table with it entries (All entries)
 */
void ht_free_table(ht_table *tablbe);

/*
 *	@brief : Increase given table size and transfer its entries to new entries that allocated
 *  But do not transer 'tombstones'
 */
void ht_adjust_table_capacity(ht_table *table, int capacity);

/*
 *	@brief : Return entry that has same key as given key , in given table
 *	Or Return NULL
 */
ht_entry *ht_table_find(ht_table *table, int capacity, const char *key);

#endif
