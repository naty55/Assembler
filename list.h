#ifndef __LIST_H
#define __LIST_H
#include "util.h"

/**
 * Char list
*/
typedef struct CharList *clist;
clist create_clist();
char append_char(clist l, char c);
char append_chars(clist l, char *items);
char append_n_chars(clist l, char *items, int size);
char clist_read_string(clist l, char * str);
char get_char_from_list(clist l, int i);
unsigned long get_length(clist l);
char * list_to_string(clist l);
clist clear_clist(clist l);
Bool is_clist_empty(clist l);
void free_clist(clist l);

/**
 * Pointer list 
*/
typedef struct PointerList *plist;
plist create_plist();
void* plist_append(plist l, void* item);
void* plist_append_if_not_null(plist l, void* item);
void* get_pointer_from_list(plist l, int i);
unsigned long get_plist_length(plist l);
plist clear_plist(plist l);
Bool is_plist_empty(plist l);
void free_plist(plist l);
#endif
