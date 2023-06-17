#ifndef __UTIL_H
#define __UTIL_H
typedef enum {
    False = 0,
    True = 1
} Bool;

char * skip_spaces(char * str);
Bool is_str_empty(char * str);

#endif