#include <stdio.h>
#include "hashmap.h"
#include "list.h"
#include "instruction_line.h"
#include "util.h"
#include "symbol.h"
/**
 * Assemvle the file
*/
void assemble(char * filename);

/**
 * Handle line with opcode 
*/
void handle_operation(char * ptr_in_line, int line_index, plist instruciton_image, ptable symbols_table, ptable missing_symbols, Bool *error);
/**
 * Fill all i_line's that are missing the label addresses (equivalent to "second phase" that was propsed in the course guide)
*/
void fill_missing_labels_addresses(ptable missing_symbols, ptable symbols_table, unsigned int instruction_image_size, Bool *error);
/**
 * Build the full binary image, data image and instruction image including the second phase
*/
void build_full_image(FILE * am_file, char * filename);
/**
 * Build binary image ("first phase")
*/
void build_image(FILE * source_file, plist instruction_image, plist data_image, ptable symbols_table, ptable missing_symbols, ptable entries, plist externals, Bool *error);
/**
 * Build specific line in the assembly code
*/
void build_assembly_lines(plist instruction_image, ptable missing_symbols, operation op, clist param1, clist param2, address_type param1_type, address_type param2_type, int param1_data, int param2_data, int line_index, int param_count);
/**
 * Validate all declared entries are defines in the file
*/
void validate_entries(ptable entries, ptable symbols_table, Bool * error);
/**
 * set the param data to i_line
*/
void handle_param(clist param, int param_data, address_type param_type, i_line line, Bool is_target, ptable missing_symbols, int line_index);
/**
 * handle data directives (.string, .data, .entry .extern)
*/
void handle_data(char * ptr_in_line, int line_index, plist data_image, ptable symbols_table, symbol sym, ptable entries, plist externals, Bool *error);
/**
 * Handle string directive
*/
void handle_string(char * ptr_in_line, int line_index, symbol sym, plist data_image, Bool * error);
/**
 * Free all global objects used during the build
*/
void free_objects(plist instruction_image, plist data_image, ptable symbols_table, ptable entries, plist externals, ptable missing_symbols);