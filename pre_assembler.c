#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "pre_assembler.h"
#include "constants.h"
#include "list.h"
#include "hashmap.h"
#include "error.h"

Bool pre_assemble(char * filename) {
    FILE * am_file;
    FILE * as_file;
    char * as_filename = concat(filename, ".as");
    char * am_filename = concat(filename, ".am");
    as_file = fopen(as_filename, "r");
    if(as_file == NULL) {
        FILE_ERROR(as_filename);
        return False;   
    }
    am_file = fopen(am_filename, "w");
    if(am_file == NULL) {
        FILE_ERROR(as_filename);
        return False;
    }
    remove_macros(as_file, am_file);
    fclose(as_file);
    fclose(am_file);
    return True;
}

int remove_macros(FILE *input_file, FILE* source_file) {
    char line[MAX_LINE_SIZE];
    char *ptr_in_line;
    clist macro_name = create_clist();
    clist macro_content;
    ptable macrosTable = create_ptable();
    while(fgets(line, MAX_LINE_SIZE, input_file) != NULL) {
        if(!clist_is_empty(macro_name)) {
            ptr_in_line = skip_spaces(line);
            if(strncmp(ENDMACRO, ptr_in_line, 7) == 0) {
                clist_clear(macro_name);
            } else {
                clist_append_chars(macro_content, line);
            }

        } else {
            ptr_in_line =  skip_spaces(line);
            if(strncmp(MACRO, ptr_in_line, 4) == 0) {
                clist_read_string(macro_name, ptr_in_line + 4);
                macro_content = create_clist();
                ptable_insert(macrosTable, clist_to_string(macro_name), macro_content);
            } else {
                char *macro_name_array;
                clist_read_string(macro_name, ptr_in_line);
                macro_name_array = clist_to_string(macro_name);
                macro_content = ptable_get(macrosTable, macro_name_array);
                if(macro_content != NULL) {
                    char *content_array = clist_to_string(macro_content);
                    fputs(content_array, source_file);
                    free(content_array);
                } else {
                    fputs(line, source_file);
                }
                clist_clear(macro_name);
                free(macro_name_array);
            }
        }
    }
    ptable_free(macrosTable, free);
    clist_free(macro_name);
    return 0;
}