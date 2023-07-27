#include "constants.h"
#include "util.h"
#include "hashmap.h"
#include "list.h"
#include "symbol.h"

Bool is_line_comment_or_blank(char * ptr_in_line);
Bool is_line_data_instruction(char * ptr_in_line);
char * read_label(char *ptr_in_line ,int line_index, ptable symbols_table, symbol* sym, unsigned int image_index, Bool *error);
char * read_operation(char * ptr_in_line, operation * op, int line_index, Bool *error);
char * get_next_param(char *ptr_in_line, clist param, Bool *read_param, int line_index, Bool *error);
char * read_next_param(char * ptr_in_line, clist param, Bool *read_param);
void check_for_extra_text(char *ptr_in_line, int line_index, Bool *error);
address_type validate_param(clist param, int *param_data, int line_index, ptable symbols_table, Bool *error);
Bool is_param_label(clist param);
char * read_data_instruction(char * ptr_in_line, data_instruction * inst, int line_index, Bool *error);
void read_data(char * ptr_in_line, int line_index, plist data_image, Bool *error);
void read_string(char * ptr_in_line, int line_index, clist str, Bool *error);
void read_externals(char * ptr_in_line, ptable symbols_table, int line_index, plist externals, Bool *error);
void read_entries(char * ptr_in_line, plist entries, int line_index, Bool *error);