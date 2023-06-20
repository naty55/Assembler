#include "constants.h"
typedef struct InstructionLine *i_line; 

i_line create_iline();
void set_source_address_type(i_line i, address_type a_type);
void set_target_address_type(i_line i, address_type a_type);
void set_encoding(i_line i, encoding e);
void set_register_source_operand(i_line i, register_name r);
void set_register_target_operand(i_line i, register_name r);
void set_label_address(i_line i, unsigned short label_address);
void set_operation(i_line i, operation op);
void set_data(i_line i, char data);
void print_i_line(i_line i);