#include <stdio.h>
#include "assembler.h"
#include "pre_assembler.h"
#include "instruction_line.h"
#include "constants.h"

int main(int argc, char const *argv[]) {
    char file_as[] = "test.as";
    char file_am[] = "test.am";
    FILE * i_file = fopen(file_as, "r");
    FILE * s_file = fopen(file_am, "w");
    remove_macros(i_file, s_file);
    fclose(i_file);
    fclose(s_file);
    s_file = fopen(file_am, "r");
    assemble(s_file);
    fclose(s_file);
    return 0;
}
