#ifndef __HASHMAP_H
#define __HASHMAP_H
#define TABLE_SIZE 64
#include "list.h"

typedef struct StringCharListTable *string_clist_table; 

string_clist_table create_string_clist_table();
string_clist_table add_to_string_clist_table(string_clist_table table, char *key, char_list list);
char_list get_from_string_clist_table(string_clist_table table, char *key);

unsigned int hashFunction(const char* key);

#endif