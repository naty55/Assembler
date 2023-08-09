#ifndef __ILINE_H
#define __ILINE_H
#include "constants.h"
/**
 * i_line represent binary line in the code 
 * It has also metadata like the index line in the final image and 
*/
typedef struct InstructionLine *i_line; 
/**
 * Create i_line
*/
i_line create_iline(unsigned long binaty_line_index);
/**
 * Get binary data part in the i_line
*/
unsigned short i_line_get_data(i_line line);
/**
 * Get the index of the line in the binary image
*/
unsigned long i_line_get_binary_line_index(i_line l);
/**
 * Set the index of the line in the binary image
*/
void i_line_set_binary_line_index(i_line l, unsigned long binary_line_index);
/**
 * Set the type of the source address paramter (9-11 bits)
*/
void i_line_set_source_address_type(i_line i, address_type a_type);
/**
 * Set the type of the source address paramter (2-4 bits)
*/
void i_line_set_target_address_type(i_line i, address_type a_type);
/**
 * Set the encoding type of the line (0-2 bits)
*/
void i_line_set_encoding(i_line i, encoding e);
/**
 * Set register as source operand (bits 7-11)
*/
void i_line_set_register_source_operand(i_line i, register_name r);
/**
 * Set register as source operand (bits 2-6)
*/
void i_line_set_register_target_operand(i_line i, register_name r);
/**
 * Set lebal address (bits 2-11)
*/
void i_line_set_label_address(i_line i, unsigned short label_address);
/**
 * Set operation of the line (5-8 bits)
*/
void i_line_set_operation(i_line i, operation op);
/**
 * Set the whole line as data
*/
void i_line_set_data_full(i_line i, short data);
/**
 * Set data as parameter (2-11 bits)
*/
void i_line_set_data(i_line i, short data);
/**
 * Set data as parameter (2-11 bits)
*/
void i_line_set_char(i_line i, char data);

#endif