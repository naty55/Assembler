#ifndef __LIST_H
#define __LIST_H
#include "util.h"

/**
 * Char list
*/
typedef struct CharList *clist;
clist create_clist();
char clist_append_char(clist l, char c);
char clist_append_chars(clist l, char *items);
char clist_append_n_chars(clist l, char *items, int size);
char clist_read_string(clist l, char * str);
char clist_get(clist l, int i);
unsigned long clist_get_length(clist l);
char * clist_to_string(clist l);
clist clist_clear(clist l);
Bool clist_is_empty(clist l);
void clist_free(clist l);

/**
 * Pointer list 
*/
typedef struct PointerList *plist;
plist create_plist();
void* plist_append(plist l, void* item);
void* plist_append_if_not_null(plist l, void* item);
void* plist_get(plist l, int i);
unsigned long plist_get_length(plist l);
Bool plist_is_empty(plist l);
void plist_free(plist l);

#endif
