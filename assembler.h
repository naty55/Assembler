#include <stdio.h>
#include "hashmap.h"
#include "list.h"
#include "instruction_line.h"
#include "util.h"
#include "symbol.h"

void assemble(FILE * source_file, char * filename);


void handle_operation(char * ptr_in_line, int line_index, plist instruciton_image, ptable symbols_table, ptable missing_symbols, Bool *error);
void fill_missing_labels_addresses(ptable missing_symbols, ptable symbols_table, unsigned int instruction_image_size, Bool *error);
void build_image(FILE * source_file, plist instruction_image, plist data_image, ptable symbols_table, ptable missing_symbols, plist entries, plist externals, Bool *error);
void validate_entries(plist entries, ptable symbols_table, Bool * error);
void handle_param(clist param, int param_data, address_type param_type, i_line line, Bool is_target, ptable missing_symbols, int line_index);
void handle_data(char * ptr_in_line, int line_index, plist data_image, ptable symbols_table, symbol sym, plist entries, plist externals, Bool *error);
void handle_string(char * ptr_in_line, int line_index, symbol sym, plist data_image, Bool * error);
void free_objects(plist instruction_image, plist data_image, ptable symbols_table, plist entries, plist externals, ptable missing_symbols);