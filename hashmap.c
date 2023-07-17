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

struct StringCharListTable {
    node * data[TABLE_SIZE];
};
clist_table create_clist_table() {
    clist_table table = malloc(sizeof(struct StringCharListTable));
    set_all_null((void**)table->data, TABLE_SIZE);
    return table;
}
clist_table add_to_clist_table(clist_table table, char *key, clist list) {
    unsigned int hash = hashFunction(key);
    node * newNode = malloc(sizeof(node));
    newNode->data = list;
    newNode->key = key;
    newNode->next = table->data[hash];
    table->data[hash] = newNode;
    return table;
}
clist get_from_clist_table(clist_table table, char *key) {
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

void free_clist_table(clist_table table) {
    int i=0;
    for (;i < TABLE_SIZE; i++) {
        node * next;
        node * ptr = table->data[i];
        while (ptr != NULL) {
            next = ptr->next;
            free(ptr->data);
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



typedef struct IntNode {
    int data;
    char * key;
    struct IntNode * next;
} int_node;

struct StringIntegerTable {
    int_node * data[TABLE_SIZE];
};
symbol_table create_int_table() {
    symbol_table table = malloc(sizeof(struct StringIntegerTable));
    set_all_null((void**)table->data, TABLE_SIZE);
    return table;
}
symbol_table add_to_int_table(symbol_table table, char *key, int data) {
    unsigned int hash = hashFunction(key);
    int_node * newNode = malloc(sizeof(int_node));
    newNode->data = data;
    newNode->key = duplicate_string(key);
    newNode->next = table->data[hash];
    table->data[hash] = newNode;
    return table;
}
int get_from_int_table(symbol_table table, char *key) {
    unsigned int hash = hashFunction(key);
    int_node * ptr = table->data[hash];
    while (ptr != NULL) {
        if(strcmp(ptr->key, key) == 0) {
            return ptr->data;
        }
        ptr = ptr->next;
    }
    return -1;
}

void free_int_table(symbol_table table) {
    int i=0;
    for (;i < TABLE_SIZE; i++) {
        int_node * next;
        int_node * ptr = table->data[i];
        while (ptr != NULL) {
            next = ptr->next;
            free(ptr->key);
            free(ptr);
            ptr = next;
            }
        }
    free(table);
}