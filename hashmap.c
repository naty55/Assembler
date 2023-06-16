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
string_clist_table add_to_string_clist_table(string_clist_table table, char *key, char_list list) {
    unsigned int hash = hashFunction(key);
    node * newNode = malloc(sizeof(node));
    newNode->data = list;
    newNode->key = key;
    newNode->next = table->data[hash];
    table->data[hash] = newNode;
    return table;
}
char_list get_from_string_clist_table(string_clist_table table, char *key) {
    unsigned int hash = hashFunction(key);
    if((table->data)[hash] != NULL) {
        return (table->data)[hash]->data;
    }
    return NULL;
}

unsigned int hashFunction(const char* key) {
    int i;
    unsigned int hash = 0;
    for (i = 0; i < strlen(key); ++i) {
        hash = hash * 31 + key[i];
    }
    return hash % TABLE_SIZE;
}