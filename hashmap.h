#ifndef __HASHMAP_H
#define __HASHMAP_H
#define TABLE_SIZE 64
#include "list.h"

typedef struct StringCharListTable *string_clist_table; 

string_clist_table create_clist_table();
string_clist_table add_to_clist_table(string_clist_table table, char *key, clist list);
clist get_from_clist_table(string_clist_table table, char *key);
void free_clist_table(string_clist_table table);
unsigned int hashFunction(const char* key);


typedef struct StringIntegerTable *int_table; 
int_table create_int_table();
int_table add_to_int_table(int_table table, char *key, int data);
int get_from_int_table(int_table table, char *key);
void free_int_table(int_table table);

#endif