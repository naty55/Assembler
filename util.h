#ifndef __UTIL_H
#define __UTIL_H
#include <stdlib.h>

typedef enum {
    False = 0,
    True = 1
} Bool;

typedef void (*freeFunction)(void *);

/**
 * Skip spaces in string, return pointer to first non-space char
*/
char * skip_spaces(char * str);
/**
 * Create boolean variable in the heap
*/
Bool * create_bool(Bool val);
/**
 * return True if the string does not contain any non-space chars
*/
Bool is_str_empty(char * str);
/**
 * Convert string to number, return True if successful
*/
Bool string_to_number(char *str, int * number);
/**
 * duplicate string in the heap
*/
char * duplicate_string(char * str);
/**
 * concat strings to new string in heap
*/
char * concat(char * str1, char * str2);
/**
 * set all cells in pointer array to NULL
*/
void set_all_null(void ** data, int size);
/**
 * Convert binary data to base64 string
*/
void convertToBase64(unsigned short value, char data[2]);
/**
 * Malloc safely - if error exit with fatal error (never return NULL)
*/
void * malloc_safe(size_t size);
/**
 * Realloc safely - if error exit with fatal error (never return NULL)
*/
void * realloc_safe(void * ptr, size_t size);
#endif