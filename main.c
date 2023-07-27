#include <stdio.h>
#include "util.h"
#include "assembler.h"
#include "error.h"
#include <stdlib.h>
#include "pre_assembler.h"

void start(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    start(argc, argv);
    return 0;
}

void start(int argc, char *argv[]) {
    char *as_filename;
    char *am_filename;
    FILE * as_file;
    FILE * am_file;
    if(argc < 2) {
        printf("Usage: assembler <file-names>\n");
        return;
    }
    argc--;
    printf("[INFO] Number of files to process: %d\n", argc);
    for (;argc > 0; argc--) {
        printf("[INFO] Working on file %s.as\n", argv[argc]);
        as_filename = concat(argv[argc], ".as");
        am_filename = concat(argv[argc], ".am");
        as_file = fopen(as_filename, "r");
        am_file = fopen(am_filename, "w");
        remove_macros(as_file, am_file);
        fclose(as_file);
        fclose(am_file);
        am_file = fopen(am_filename, "r");
        assemble(am_file, argv[argc]);
        fclose(am_file);
        free(as_filename);
        free(am_filename);
    }
}