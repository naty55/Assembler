#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "pre_assembler.h"
#include "constants.h"
#include "list.h"
#include "hashmap.h"

int remove_macros(FILE *input_file, FILE* source_file) {
    char line[MAX_LINE_SIZE];
    char *ptr_in_line;
    clist macro_name = create_clist();
    clist macro_content;
    ptable macrosTable = create_ptable();
    while(fgets(line, MAX_LINE_SIZE, input_file) != NULL) {
        if(!is_clist_empty(macro_name)) {
            ptr_in_line = skip_spaces(line);
            if(strncmp(ENDMACRO, ptr_in_line, 7) == 0) {
                clear_clist(macro_name);
            } else {
                append_chars(macro_content, line);
            }

        } else {
            ptr_in_line =  skip_spaces(line);
            if(strncmp(MACRO, ptr_in_line, 4) == 0) {
                clist_read_string(macro_name, ptr_in_line + 4);
                macro_content = create_clist();
                ptable_insert(macrosTable, list_to_string(macro_name), macro_content);
            } else {
                char *macro_name_array;
                clist_read_string(macro_name, ptr_in_line);
                macro_name_array = list_to_string(macro_name);
                macro_content = ptable_get(macrosTable, macro_name_array);
                if(macro_content != NULL) {
                    char *content_array = list_to_string(macro_content);
                    fputs(content_array, source_file);
                    free(content_array);
                } else {
                    fputs(line, source_file);
                }
                clear_clist(macro_name);
                free(macro_name_array);
            }
        }
    }
    free_ptable(macrosTable, free);
    free_clist(macro_name);
    return 0;
}