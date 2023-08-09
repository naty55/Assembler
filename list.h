#ifndef __LIST_H
#define __LIST_H
#include "util.h"

/**
 * Char list
*/
typedef struct CharList *clist;
/**
 * Create an empty list of charecters 
 * the list is dyanmically allocating memory,
 * doubling the size every time the list is full.
 * 
*/
clist create_clist();
/**
 * Add char c to the end of the list
*/
char clist_append_char(clist l, char c);
/**
 * Add bulk of chars to the end of the list (until we get '\0' char)
*/
char clist_append_chars(clist l, char *items);
/**
 * Add bulk of n chars to the end of the list
*/
char clist_append_n_chars(clist l, char *items, int size);
/**
 * Add bulk of chars (until we get '\0' space or newline charecter)
*/
char clist_read_string(clist l, char * str);
/**
 * Get char at index i
*/
char clist_get(clist l, int i);
/**
 * Get the length of the clist l
*/
unsigned long clist_get_length(clist l);
/**
 * Convert the clist into a string (mew memory allocation)
*/
char * clist_to_string(clist l);
/**
 * delete all chars in the clist (actually just set the end index to 0)
*/
clist clist_clear(clist l);
/**
 * Return True if the list is empty (length is 0)
*/
Bool clist_is_empty(clist l);
/**
 * Free the clist
*/
void clist_free(clist l);

/**
 * Pointer list 
*/
typedef struct PointerList *plist;
/**
 * Create an empty list of pointers, 
 * the list is dyanmically allocating memory,
 * doubling the size every time the list is full.
 * 
*/
plist create_plist();
/**
 * Add pointer to the end of plist l
*/
void* plist_append(plist l, void* item);
/**
 * Add pointer to the end of plist only if the pointer is not NULL
*/
void* plist_append_if_not_null(plist l, void* item);
/**
 * Get pointer from plist at index i
*/
void* plist_get(plist l, int i);
/**
 * Get plist length 
 * Note: it's not the memory size - but a number of items stroed in the list.
*/
unsigned long plist_get_length(plist l);
/**
 * Return True if plist is empty
 * equivalent to plist_get_length(l) == 0
*/
Bool plist_is_empty(plist l);
/**
 * free the plist and all the objects which their pointers stored in it
*/
void plist_free_all(plist l);
/**
 * Free plist sturct only, not the pointers themselves
*/
void plist_free(plist l);

#endif
