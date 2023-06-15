#include "list.h"
#include <stdlib.h>

struct CharList {
    char *data;
    unsigned long length;
    unsigned long size;
};

char_list create_char_list() {
    char_list list = malloc(sizeof(struct CharList));
    list->data=NULL;
    list->size = 0; 
    list->length = 0;
    return list;
}

char append_char(char_list l, char c) {
    if (l->size == l->length) /* We are out of place*/
    {
        l->data = realloc(l->data, 2 * l->size * sizeof(char));
        l->size = 2 * l->size;
    }
    l->data[l->length++] = c;
    return c;
}
char append_all_chars(char_list l, char *items, int size) {
    int i;
    for (i = 0; i < size; i++) {
        append_char(l, items[i]);
    }
    return items[i];
}
char get_char_from_list(char_list l, int i) {
    return (l->data)[i];
}