#include "list.h"
#include "hashmap.h"
#include "string.h"
#include <stdlib.h>

typedef struct Node {
    void * data;
    char *key;
    struct Node * next;
} node;

struct StringCharListTable {
    node * data[TABLE_SIZE];
};
string_clist_table create_string_clist_table() {
    string_clist_table table = malloc(sizeof(struct StringCharListTable));
    return table;
}
string_clist_table add_to_string_clist_table(string_clist_table table, char *key, clist list) {
    unsigned int hash = hashFunction(key);
    node * newNode = malloc(sizeof(node));
    newNode->data = list;
    newNode->key = key;
    newNode->next = table->data[hash];
    table->data[hash] = newNode;
    return table;
}
clist get_from_string_clist_table(string_clist_table table, char *key) {
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

void free_clist_table(string_clist_table table) {
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