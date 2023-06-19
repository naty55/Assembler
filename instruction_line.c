#include "instruction_line.h"
#include <stdlib.h>

void printBinaryWithUnderscore(unsigned short value) {
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
struct InstructionLine {
    unsigned short data;
};
i_line create_iline() {
    i_line il = malloc(sizeof(struct InstructionLine));
    il->data = 0;
    return il;
}

void set_source_address_type(i_line i, address_type a_type) {
    i->data = (i->data & 0xFE3) | (a_type << 2);
    printBinaryWithUnderscore(i->data);
}
void set_target_address_type(i_line i, address_type a_type) {
    i->data = (i->data & 0x1FF) | (a_type << 9);
    printBinaryWithUnderscore(i->data);
}

void set_encoding(i_line i, encoding e) {
    i->data = (i->data & 0xFFC) | e;
    printBinaryWithUnderscore(i->data);
}
void set_register_source_operand(i_line i) {

}
void set_register_target_operand(i_line i) {

}
void set_label_operand(i_line i) {

}

void set_operation(i_line i, operation op) {
    i->data = (i->data & 0xF1E) | (op << 5);
    printBinaryWithUnderscore(i->data);
}