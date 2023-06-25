#include "constants.h"
#include "util.h"
#include "list.h"

Bool is_line_comment_or_blank(char * ptr_in_line);
Bool is_line_data_instruction(char * ptr_in_line);
char * read_label(char *ptr_in_line ,int line_index);
char * read_operation(char * ptr_in_line, operation * op, int line_index);
char * get_next_param(char *ptr_in_line, clist param, Bool *read_param, int line_index);
void check_for_extra_text(char *ptr_in_line, int line_index);