#include <stdio.h>
#include "hashmap.h"
#include "list.h"
#include "instruction_line.h"
#include "util.h"
#include "symbol.h"

void assemble(char * filename);


void handle_operation(char * ptr_in_line, int line_index, plist instruciton_image, ptable symbols_table, ptable missing_symbols, Bool *error);
void fill_missing_labels_addresses(ptable missing_symbols, ptable symbols_table, unsigned int instruction_image_size, Bool *error);
void build(FILE * am_file, char * filename);
void build_image(FILE * source_file, plist instruction_image, plist data_image, ptable symbols_table, ptable missing_symbols, ptable entries, plist externals, Bool *error);
void build_assembly_lines(plist instruction_image, ptable missing_symbols, operation op, clist param1, clist param2, address_type param1_type, address_type param2_type, int param1_data, int param2_data, int line_index, int param_count);
void validate_entries(ptable entries, ptable symbols_table, Bool * error);
void handle_param(clist param, int param_data, address_type param_type, i_line line, Bool is_target, ptable missing_symbols, int line_index);
void handle_data(char * ptr_in_line, int line_index, plist data_image, ptable symbols_table, symbol sym, ptable entries, plist externals, Bool *error);
void handle_string(char * ptr_in_line, int line_index, symbol sym, plist data_image, Bool * error);
void free_objects(plist instruction_image, plist data_image, ptable symbols_table, ptable entries, plist externals, ptable missing_symbols);