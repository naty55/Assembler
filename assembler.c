#include <stdio.h>
#include "assembler.h"
#include "pre_assembler.h"
#include "instruction_line.h"
#include "constants.h"

int main(int argc, char const *argv[]) {
    i_line il = create_iline();
    set_encoding(il, A);
    set_operation(il, MOV);
    set_target_address_type(il, IMM_ADDR);
    set_source_address_type(il, IMM_REG_ADDR);
    print_i_line(il);
    i_line il1 = create_iline();
    set_encoding(il1, A);
    set_register_source_operand(il1, R3);
    print_i_line(il1);
    i_line il2 = create_iline();
    set_encoding(il1, R);
    set_label_address(il1, 125);
    print_i_line(il1);
    set_data(il2, 'b');
    print_i_line(il2);
    /*
    FILE * i_file = fopen("test.as", "r");
    FILE * s_file = fopen("test.am", "w");
    remove_macros(i_file, s_file);
    fclose(i_file);
    fclose(s_file);
    */
    return 0;
}
