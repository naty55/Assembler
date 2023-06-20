#include "list.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "util.h"

struct CharList {
    char *data;
    unsigned long length;
    unsigned long size;
};

clist create_clist() {
    clist list = malloc(sizeof(struct CharList));
    list->data= malloc(1);
    list->size = 1; 
    list->length = 0;
    return list;
}

char append_char(clist l, char c) {
    if (l->size == l->length) /* We are out of place*/
    {
        l->data = realloc(l->data, 2 * l->size * sizeof(char));
        l->size = 2 * l->size;
    }
    l->data[l->length++] = c;
    return c;
}
char append_n_chars(clist l, char *items, int size) {
    int i;
    for (i = 0; i < size; i++) {
        append_char(l, items[i]);
    }
    return items[i];
}

char append_chars(clist l, char *items) {
    int i;
    for (i = 0; items[i] != 0; i++) {
        append_char(l, items[i]);
    }
    return items[i];
}

char read_string(clist l, char * str) {
    str = skip_spaces(str);
    while(!isspace(*str) && *str != '\n' && *str != '\0') {
        append_char(l, *str);
        str++;
    }
    return *(str - 1);
}

char get_char_from_list(clist l, int i) {
    return (l->data)[i];
}

unsigned long get_length(clist l) {
    return l->length;
}

char * list_to_string(clist l) {
    char * str = malloc((l->length + 1) * sizeof(char));
    strncpy(str, l->data, l->length);
    str[l->length] = '\0';
    return str;
}

clist clear_clist(clist l) {
    l->length = 0;
    return l;
}
Bool is_clist_empty(clist l) {
    return (Bool)(l->length == 0);
}

void free_clist(clist l) {
    free(l->data);
    free(l);
}

struct PointerList {
    void **data;
    unsigned long length;
    unsigned long size;
};
plist create_plist() {
    plist list = malloc(sizeof(struct PointerList));
    list->data= malloc(sizeof(void *));
    list->size = 1; 
    list->length = 0;
    return list;
}
void* append_pointer(plist l, void* item) {
     if (l->size == l->length) /* We are out of place*/
    {
        l->data = realloc(l->data, 2 * l->size * sizeof(void *));
        l->size = 2 * l->size;
    }
    l->data[l->length++] = item;
    return item;
}
void* get_pointer_from_list(plist l, int i) {
    return l->data[i];
}
unsigned long get_plist_length(plist l) {
    return l->length;
}
plist clear_plist(plist l) {
    int i;
    for (i = 0; i < l->length; i++) {
        free(l->data[i]);
    }
    l->length=0;
    return l;
}
Bool is_plist_empty(plist l) {
    return (Bool)(l->length == 0);
}
void free_plist(plist l) {
    clear_plist(l);
    free(l);
}
