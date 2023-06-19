#include "instruction_line.h"
#include "util.h"
#include <stdlib.h>

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
}
void set_target_address_type(i_line i, address_type a_type) {
    i->data = (i->data & 0x1FF) | (a_type << 9);
}

void set_encoding(i_line i, encoding e) {
    i->data = (i->data & 0xFFC) | e;
}
void set_register_source_operand(i_line i) {

}
void set_register_target_operand(i_line i) {

}
void set_label_operand(i_line i) {

}

void set_operation(i_line i, operation op) {
    i->data = (i->data & 0xF1E) | (op << 5);
}

void print_i_line(i_line i) {
    printBinary(i->data);
}