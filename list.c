#include "list.h"
#include <stdlib.h>
#include <string.h>
#include "util.h"

struct CharList {
    char *data;
    unsigned long length;
    unsigned long size;
};

char_list create_char_list() {
    char_list list = malloc(sizeof(struct CharList));
    list->data= malloc(1);
    list->size = 1; 
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
char append_n_chars(char_list l, char *items, int size) {
    int i;
    for (i = 0; i < size; i++) {
        append_char(l, items[i]);
    }
    return items[i];
}

char append_chars(char_list l, char *items) {
    int i;
    for (i = 0; items[i] != 0; i++) {
        append_char(l, items[i]);
    }
    return items[i];
}

char read_string(char_list l, char * str) {
    str = skip_spaces(str);
    while(!isspace(*str) && *str != '\n' && *str != '\0') {
        append_char(l, *str);
        str++;
    }
    return *(str - 1);
}

char get_char_from_list(char_list l, int i) {
    return (l->data)[i];
}

unsigned long get_length(char_list l) {
    return l->length;
}

char * list_to_string(char_list l) {
    char * str = malloc((l->length + 1) * sizeof(char));
    strncpy(str, l->data, l->length);
    str[l->length] = '\0';
    return str;
}

char_list clear_list(char_list l) {
    l->length = 0;
}
Bool is_empty(char_list l) {
    return (Bool)(l->length == 0);
}

void free_list(char_list l) {
    free(l->data);
    free(l);
}
