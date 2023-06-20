#ifndef __LIST_H
#define __LIST_H
#include "util.h"
typedef struct CharList *clist;

clist create_char_list();
char append_char(clist l, char item);
char append_chars(clist l, char *items);
char append_n_chars(clist l, char *items, int size);
char read_string(clist l, char * str);
char get_char_from_list(clist l, int i);
unsigned long get_length(clist l);
char * list_to_string(clist l);
clist clear_clist(clist l);
Bool is_clist_empty(clist l);
void free_clist(clist l);
#endif
