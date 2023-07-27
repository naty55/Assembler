#include <ctype.h>
#include <stdio.h>
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include "error.h"



char * skip_spaces(char * str) {
    while (isspace(*(str++)));
    return --str;
}
Bool is_str_empty(char * str) {
    return (Bool)(*skip_spaces(str) == '\0');
}

Bool string_to_number(char *str, int * number) {
    int sign = 1;
    Bool hasDigits;
    *number = 0;
    str = skip_spaces(str);
    if (*str == '-') {
        sign = -1;
        str++;
    } else if(*str == '+') {
        str++;
    }

    hasDigits = False;
    while (*str >= '0' && *str <= '9') {
        hasDigits = True;
        *number *= 10;
        *number += *str - '0';
        str++;
    }
    *number *= sign;
    return is_str_empty(str) && hasDigits;
}

char * duplicate_string(char * str){
    size_t length = strlen(str);
    char* duplicate = (char*)malloc_safe((length + 1) * sizeof(char));
    strcpy(duplicate, str);
    return duplicate;
}

char * concat(char * str1, char * str2) {
    size_t length = strlen(str1) + strlen(str2);
    char* duplicate = (char*)malloc_safe((length + 1) * sizeof(char));
    strcpy(duplicate, str1);
    strcat(duplicate, str2);
    return duplicate;
}

void set_all_null(void ** data, int size) {
    int i = 0;
    for (; i < size; i++) {
        *data = NULL;
        data++;
    }
}

void convertToBase64(unsigned short value, char data[2]) {
    const char base64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i;
    for (i = 0; i < 2; i++) {
        unsigned short chunk = (value >> ((1- i)  * 6)) & 0x3F;
        data[i] = base64Table[chunk];
    }
}

void * malloc_safe(size_t size) {
    void * ptr = malloc(size);
    if(ptr == NULL) {
        FATAL_ERROR("Couldn't allocate memory");
    }
    return ptr;
}

void * realloc_safe(void * ptr, size_t size) {
    ptr = realloc(ptr, size);
    if(ptr == NULL) {
        FATAL_ERROR("Couldn't allocate memory");
    }
    return ptr;
}