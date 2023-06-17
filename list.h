#ifndef __LIST_H
#define __LIST_H
#include "util.h"
typedef struct CharList *char_list;

char_list create_char_list();
char append_char(char_list l, char item);
char append_chars(char_list l, char *items);
char append_n_chars(char_list l, char *items, int size);
char read_string(char_list l, char * str);
char get_char_from_list(char_list l, int i);
unsigned long get_length(char_list l);
char * list_to_string(char_list l);
char_list clear_list(char_list l);
Bool is_empty(char_list l);
void free_list(char_list l);
#endif
