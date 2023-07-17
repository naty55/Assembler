#ifndef __UTIL_H
#define __UTIL_H
typedef enum {
    False = 0,
    True = 1
} Bool;

char * skip_spaces(char * str);
Bool is_str_empty(char * str);
void printBinary(unsigned short value);
Bool is_string_number(char *str);
char * duplicate_string(char * str);
void set_all_null(void ** data, int size);
#endif