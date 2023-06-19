#include "constants.h"
typedef struct InstructionLine *i_line; 

void set_source_operand_type(i_line i);
void set_target_operand_type(i_line i);
void set_encoding(i_line i, encoding e);
void set_source_operand(i_line i);
void set_target_operand(i_line i);
void set_operation(i_line i);