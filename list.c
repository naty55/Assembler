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
    clist list = malloc_safe(sizeof(struct CharList));
    list->data= malloc_safe(1);
    list->size = 1; 
    list->length = 0;
    return list;
}

char clist_append_char(clist l, char c) {
    if (l->size == l->length) /* We are out of place*/
    {
        l->data = realloc_safe(l->data, 2 * l->size * sizeof(char));
        l->size = 2 * l->size;
    }
    l->data[l->length++] = c;
    return c;
}
char clist_append_n_chars(clist l, char *items, int size) {
    int i;
    for (i = 0; i < size; i++) {
        clist_append_char(l, items[i]);
    }
    return items[i];
}

char clist_append_chars(clist l, char *items) {
    int i;
    for (i = 0; items[i] != 0; i++) {
        clist_append_char(l, items[i]);
    }
    return items[i];
}

char clist_read_string(clist l, char * str) {
    str = skip_spaces(str);
    while(!isspace(*str) && *str != '\n' && *str != '\0') {
        clist_append_char(l, *str);
        str++;
    }
    return *(str - 1);
}

char clist_get(clist l, int i) {
    return (l->data)[i];
}

unsigned long clist_get_length(clist l) {
    return l->length;
}

char * clist_to_string(clist l) {
    char * str = malloc_safe((l->length + 1) * sizeof(char));
    strncpy(str, l->data, l->length);
    str[l->length] = '\0';
    return str;
}

clist clist_clear(clist l) {
    l->length = 0;
    return l;
}
Bool clist_is_empty(clist l) {
    return (Bool)(l->length == 0);
}

void clist_free(clist l) {
    free(l->data);
    free(l);
}

struct PointerList {
    void **data;
    unsigned long length;
    unsigned long size;
};
plist create_plist() {
    plist list = malloc_safe(sizeof(struct PointerList));
    list->data= malloc_safe(sizeof(void *));
    list->size = 1; 
    list->length = 0;
    return list;
}
void* plist_append(plist l, void* item) {
     if (l->size == l->length) /* We are out of place*/
    {
        l->data = realloc_safe(l->data, 2 * l->size * sizeof(void *));
        l->size = 2 * l->size;
    }
    l->data[l->length++] = item;
    return item;
}

void* plist_append_if_not_null(plist l, void* item) {
    if(item != NULL) {
        return plist_append(l, item);
    }
    return item;
}

void* plist_get(plist l, int i) {
    return l->data[i];
}
unsigned long plist_get_length(plist l) {
    return l->length;
}

Bool plist_is_empty(plist l) {
    return (Bool)(l->length == 0);
}
void plist_free(plist l) {
    int i;
    for (i = 0; i < l->length; i++) {
        free(l->data[i]);
    }
    free(l);
}
