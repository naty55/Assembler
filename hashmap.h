#ifndef __HASHMAP_H
#define __HASHMAP_H
#define TABLE_SIZE 64
#include "list.h"

typedef struct StringCharListTable *string_clist_table; 

string_clist_table create_string_clist_table();
string_clist_table add_to_string_clist_table(string_clist_table table, char *key, clist list);
clist get_from_string_clist_table(string_clist_table table, char *key);
void free_clist_table(string_clist_table table);
unsigned int hashFunction(const char* key);

#endif