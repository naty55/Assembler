#ifndef __UTIL_H
#define __UTIL_H
#include <stdlib.h>

typedef enum {
    False = 0,
    True = 1
} Bool;

typedef void (*freeFunction)(void *);


char * skip_spaces(char * str);
Bool * create_bool(Bool val);
Bool is_str_empty(char * str);
Bool string_to_number(char *str, int * number);
char * duplicate_string(char * str);
char * concat(char * str1, char * str2);
void set_all_null(void ** data, int size);
void convertToBase64(unsigned short value, char data[2]);
void * malloc_safe(size_t size);
void * realloc_safe(void * ptr, size_t size);
#endif