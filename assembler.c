#include <stdio.h>
#include "assembler.h"
#include "pre_assembler.h"

int main(int argc, char const *argv[]) {
    FILE * i_file = fopen("test.as", "r");
    FILE * s_file = fopen("test.am", "w");
    remove_macros(i_file, s_file);
    fclose(i_file);
    fclose(s_file);
    return 0;
}
