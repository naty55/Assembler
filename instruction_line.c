#include "instruction_line.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

const char base64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void convertToBase64(unsigned short value) {
    char base64Result[2];
    int i;
    for (i = 0; i < 2; i++) {
        unsigned short chunk = (value >> ((1- i)  * 6)) & 0x3F;
        base64Result[i] = base64Table[chunk];
    }
    printf("Base64 encoding: %s\n", base64Result);
}

struct InstructionLine {
    unsigned short data;
};
i_line create_iline() {
    i_line il = malloc(sizeof(struct InstructionLine));
    il->data = 0;
    return il;
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

void set_data(i_line i, char data) {
    i->data = (i->data & 0x000) | data;
}

void set_operation(i_line i, operation op) {
    i->data = (i->data & 0xF1E) | (op << 5);
}

void print_i_line(i_line i) {
    printBinary(i->data);
    convertToBase64(i->data);
}