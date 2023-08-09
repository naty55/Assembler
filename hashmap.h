#ifndef __HASHMAP_H
#define __HASHMAP_H
#define TABLE_SIZE 64
#include "list.h"
/**
 * Table <String, Pointer>
*/
typedef struct StringPointerTable *ptable;
/**
 * create ptable, key is string and value is pointer
*/
ptable create_ptable();
/**
 * Insert value to table
 * Note: if the key already exists in the table it will not be overrided, 
 * but both old and new values will stay in the table and can result unexpected behaviour, 
 * so before inserting new value check the key does not exists
*/
ptable ptable_insert(ptable table, char *key, void* ptr);
/**
 * Get value from the table with key
*/
void* ptable_get(ptable table, char *key);
/** 
 * Return new plist with all keys stored in the ptable
*/
plist ptable_get_keys(ptable table);
/**
 * Free the table data, with specified free function for objects
*/
void ptable_free(ptable table, freeFunction free_function);

/**
 * Hash funciton used to calculate the hash of a key
*/
unsigned int hashFunction(const char* key);

#endif