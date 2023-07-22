#include <stdio.h>
#include "util.h"
#include "assembler.h"
#include <stdlib.h>
#include "pre_assembler.h"
#include "instruction_line.h"
#include "constants.h"

void start(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    start(argc, argv);
    return 0;
}

void start(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: assembler <file-names>\n");
        return;
    }
    argc--;
    printf("[INFO] Number of files to process: %d\n", argc);
    for (;argc > 0; argc--) {
        printf("[INFO] Working on file %s.as\n", argv[argc]);
        char * as_filename = concat(argv[argc], ".as");
        char * am_filename = concat(argv[argc], ".am");
        FILE * i_file = fopen(as_filename, "r");
        FILE * s_file = fopen(am_filename, "w");
        remove_macros(i_file, s_file);
        fclose(i_file);
        fclose(s_file);
        s_file = fopen(am_filename, "r");
        assemble(s_file, argv[argc]);
        fclose(s_file);
        free(as_filename);
        free(am_filename);
    }
}