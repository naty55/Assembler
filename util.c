#include <ctype.h>
#include <stdio.h>
#include "util.h"



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