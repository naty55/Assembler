#include "list.h"
#include "hashmap.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

typedef struct Node {
    void * data;
    char * key;
    struct Node * next;
} node;

struct StringPointerTable {
    node * data[TABLE_SIZE];
};

ptable create_ptable() {
    ptable table = malloc(sizeof(struct StringPointerTable));
    set_all_null((void**)table->data, TABLE_SIZE);
    return table;
}

ptable ptable_insert(ptable table, char *key, void* ptr) {
    unsigned int hash = hashFunction(key);
    node * newNode = malloc(sizeof(node));
    newNode->data = ptr;
    newNode->key = duplicate_string(key);
    newNode->next = table->data[hash];
    table->data[hash] = newNode;
    return table;
}

void* ptable_get(ptable table, char *key) {
    unsigned int hash = hashFunction(key);
    node * ptr = table->data[hash];
    while (ptr != NULL) {
        if(strcmp(ptr->key, key) == 0) {
            return ptr->data;
        }
        ptr = ptr->next;
    }
    return NULL;
}

plist ptable_get_keys(ptable table) {
    int i = 0;
    plist keys = create_plist();
    for (;i < TABLE_SIZE; i++) {
        node * next;
        node * ptr = table->data[i];
        while (ptr != NULL) {
            next = ptr->next;
            plist_append(keys, duplicate_string(ptr->key));
            ptr = next;
        }
    }
    return keys;
}

void free_ptable(ptable table, freeFunction free_function) {
    int i=0;
    for (;i < TABLE_SIZE; i++) {
        node * next;
        node * ptr = table->data[i];
        while (ptr != NULL) {
            next = ptr->next;
            free_function(ptr->data);
            free(ptr->key);
            free(ptr);
            ptr = next;
        }
    }
    free(table);
}

unsigned int hashFunction(const char* key) {
    int i;
    unsigned int hash = 0;
    for (i = 0; i < strlen(key); ++i) {
        hash = hash * 31 + key[i];
    }
    return hash % TABLE_SIZE;
}
