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
    if(argc < 2) {
        printf("Usage: assembler <file-names>\n");
        return;
    }
    argc--;
    INFO_1PARAM_INT("Number of files to process:", argc);
    for (;argc > 0; argc--) {
        Bool hasError = False;
        INFO_WORKING_ON_FILE(argv[argc])
        hasError = !pre_assemble(argv[argc]);
        if(hasError) {
            continue;
        }
        INFO("Start assembling");
        assemble(argv[argc]);
    }
}