#include <stdio.h>
#include "assembler.h"
#include "pre_assembler.h"
#include "instruction_line.h"
#include "constants.h"

int main(int argc, char const *argv[]) {
    i_line il = create_iline();
    set_encoding(il, R);
    set_operation(il, STP);
    set_source_address_type(il, IMM_ADDR);
    set_target_address_type(il, IMM_REG_ADDR);
    /*
    FILE * i_file = fopen("test.as", "r");
    FILE * s_file = fopen("test.am", "w");
    remove_macros(i_file, s_file);
    fclose(i_file);
    fclose(s_file);
    */
    return 0;
}
