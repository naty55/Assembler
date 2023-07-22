#include "constants.h"
typedef struct InstructionLine *i_line; 

i_line create_iline(unsigned long binaty_line_index);
unsigned short i_line_get_data(i_line line);
unsigned long i_line_get_binary_line_index(i_line l);
void i_line_set_binary_line_index(i_line l, unsigned long binary_line_index);
void set_source_address_type(i_line i, address_type a_type);
void set_target_address_type(i_line i, address_type a_type);
void set_encoding(i_line i, encoding e);
void set_register_source_operand(i_line i, register_name r);
void set_register_target_operand(i_line i, register_name r);
void set_label_address(i_line i, unsigned short label_address);
void set_operation(i_line i, operation op);
void set_data_full(i_line i, short data);
void set_data(i_line i, short data);
void set_char(i_line i, char data);
void print_i_line(i_line i);
void print_iline_in_base64(i_line i);