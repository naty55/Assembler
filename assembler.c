#include <stdio.h>
#include "list.h"
#include "instruction_line.h"
#include "constants.h"

Bool is_line_comment_or_blank(char * ptr_in_line);

void assemble(FILE * source_file) {
    char line[MAX_LINE_SIZE];
    char *ptr_in_line;
    int i = 0;
    plist insturction_image = create_plist();
    plist data_image = create_plist();
    while(fgets(line, MAX_LINE_SIZE, source_file) != NULL) {
        ptr_in_line = skip_spaces(line);
        if(is_line_comment_or_blank(ptr_in_line)) {
            continue;
        } else {
            printf("%d\t: %s", i++, line);
        }
    }
    printf("\n");
}

Bool is_line_comment_or_blank(char * ptr_in_line) {
    return (Bool)(*ptr_in_line == ';' || *ptr_in_line == '\0');
}