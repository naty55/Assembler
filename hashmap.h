#ifndef __HASHMAP_H
#define __HASHMAP_H
#define TABLE_SIZE 64
#include "list.h"

typedef struct StringPointerTable *ptable;

ptable create_ptable();
ptable ptable_insert(ptable table, char *key, void* ptr);
void* ptable_get(ptable table, char *key);
plist ptable_get_keys(ptable table);
void free_ptable(ptable table);
unsigned int hashFunction(const char* key);

#endif