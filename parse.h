#ifndef __PARSE_H
#define __PARSE_H

#include "constants.h"
#include "util.h"
#include "hashmap.h"
#include "list.h"
#include "symbol.h"

#define READ_COMMA() \
ptr_in_line = skip_spaces(ptr_in_line); \
if(*ptr_in_line == ',') { \
            ptr_in_line++; \
        } else if(*ptr_in_line != '\0'){ \
            HANDLE_ERROR("Missing comma between params", line_index, error); \
            clist_free(param); \
            return; \
        } \
/**
 * Return True if line is comment or blank
*/
Bool is_line_comment_or_blank(char * ptr_in_line);
/**
 * Return True if line is data directive (starts with '.')
*/
Bool is_line_data_instruction(char * ptr_in_line);
/**
 * Read label
*/
char * read_label(char *ptr_in_line ,int line_index, ptable symbols_table, symbol* sym, unsigned int image_index, Bool *error);
/**
 * Read opcode
*/
char * read_operation(char * ptr_in_line, operation * op, int line_index, Bool *error);
/**
 * get the next param, read ',' and then read param
*/
char * get_next_param(char *ptr_in_line, clist param, Bool *read_param, int line_index, Bool *error);
/**
 * Read next param (until ',' or EOL)
*/
char * read_next_param(char * ptr_in_line, clist param, Bool *read_param);
/**
 * check after end of line no extra text 
*/
void check_for_extra_text(char *ptr_in_line, int line_index, Bool *error);
/**
 * Validate param and return the param_type 
*/
address_type validate_param(clist param, int *param_data, int line_index, ptable symbols_table, Bool *error);
/**
 * return True if param is of type label
*/
Bool is_param_label(clist param);
/**
 * 
*/
Bool is_param_label1(char * param);
/**
 * Read the data instruction type (.entry, .data, .string, .extern)
*/
char * read_data_instruction(char * ptr_in_line, data_instruction * inst, int line_index, Bool *error);
/**
 * Read .data directive
*/
void read_data(char * ptr_in_line, int line_index, plist data_image, Bool *error);
/**
 * read .string directive
*/
void read_string(char * ptr_in_line, int line_index, clist str, Bool *error);
/**
 * read .extern directive
*/
void read_externals(char * ptr_in_line, ptable symbols_table, int line_index, plist externals, Bool *error);
/**
 * read .entry directive
*/
void read_entries(char * ptr_in_line, ptable entries, int line_index, Bool *error);


#endif