#include "instruction_line.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

struct InstructionLine {
    unsigned short data;
    unsigned long binary_line_index;
};
i_line create_iline(unsigned long binaty_line_index) {
    i_line il = malloc_safe(sizeof(struct InstructionLine));
    il->data = 0;
    il->binary_line_index = binaty_line_index;
    return il;
}

unsigned short i_line_get_data(i_line line) {
    return line->data;
}

unsigned long i_line_get_binary_line_index(i_line l) {
    return l->binary_line_index;
}

void i_line_set_binary_line_index(i_line l, unsigned long binary_line_index) {
    l->binary_line_index = binary_line_index;
}

void set_target_address_type(i_line i, address_type a_type) {
    i->data = (i->data & 0xFE3) | (a_type << 2);
}
void set_source_address_type(i_line i, address_type a_type) {
    i->data = (i->data & 0x1FF) | (a_type << 9);
}

void set_encoding(i_line i, encoding e) {
    i->data = (i->data & 0xFFC) | e;
}
void set_register_source_operand(i_line i, register_name r) {
    i->data = (i->data & 0x7F) |  (r << 7);
}
void set_register_target_operand(i_line i, register_name r) {
    i->data = (i->data & 0xF83) |  (r << 2);
}
void set_label_address(i_line i, unsigned short label_address) {
    i->data = (i->data & 0x003) | (label_address << 2);
}

void set_data_full(i_line i, short data) {
    if(data < 0) {
        i->data = (1 << 12) + data;
    } else {
        i->data = (i->data & 0x000) | (data);
    }
}

void set_char(i_line i, char data) {
    i->data = (i->data & 0x003) | data;
}

void set_data(i_line i, short data) {
    if(data < 0) {
        i->data = (1 << 12) + (data << 2);
    } else {
        i->data = (i->data & 0x000) | (data << 2);
    }
}

void set_operation(i_line i, operation op) {
    i->data = (i->data & 0xF1E) | (op << 5);
}


void printBinary(unsigned short value) {
    int numBits = sizeof(value) * 8; 
    int numPrintedBits = 0; 
    int i;
    printf("FREE: ");
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

void print_i_line(i_line i) {
    if(i == NULL) {
        printf("NULL\n");
        return;
    }
    printBinary(i->data);
}