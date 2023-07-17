#include <ctype.h>
#include <stdio.h>
#include "util.h"
#include <stdlib.h>
#include <string.h>



char * skip_spaces(char * str) {
    while (isspace(*(str++)));
    return --str;
}
Bool is_str_empty(char * str) {
    return (Bool)(*skip_spaces(str) == '\0');
}


void printBinary(unsigned short value) {
    int numBits = sizeof(value) * 8; 
    int numPrintedBits = 0; 
    int i;
    for (i = numBits - 1; i >= 0; i--) {
        unsigned short mask = 1 << i;
        unsigned short bit = (value & mask) >> i;
        printf("%u", bit);

        numPrintedBits++;

        if (numPrintedBits % 4 == 0 && numPrintedBits != numBits)
            printf("_");
    }
    printf("\n");
}

Bool is_string_number(char *str) {
    int i = 0;
    Bool hasDigits;
    while (isspace(str[i])) {
        i++;
    }

    if (str[i] == '-' || str[i] == '+') {
        i++;
    }
    hasDigits = False;
    while (str[i] >= '0' && str[i] <= '9') {
        hasDigits = True;
        i++;
    }
    if (str[i] == '.') {
        i++;
        while (str[i] >= '0' && str[i] <= '9') {
            hasDigits = True;
            i++;
        }
    }
    while (isspace(str[i])) {
        i++;
    }
    if(str[i] == '\0' && hasDigits) {
        return True;
    }
    return False;
}

char * duplicate_string(char * str){
    
    size_t length = strlen(str);
    char* duplicate = (char*)malloc((length + 1) * sizeof(char));
    strcpy(duplicate, str);
    return duplicate;
}


void set_all_null(void ** data, int size) {
    int i = 0;
    for (; i < size; i++) {
        *data = NULL;
        data++;
    }
}