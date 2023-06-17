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
    int i = 0;
    char_list macro_name = create_char_list();
    char_list macro_content;
    string_clist_table macrosTable = create_string_clist_table();
    while(fgets(line, MAX_LINE_SIZE, input_file) != NULL) {
        printf("%d\t: %s", i++, line);
        if(!is_empty(macro_name)) {
            ptr_in_line = skip_spaces(line);
            if(strncmp(ENDMACRO, ptr_in_line, 7) == 0) {
                clear_list(macro_name);
            } else {
                append_chars(macro_content, line);
            }

        } else {
            ptr_in_line =  skip_spaces(line);
            if(strncmp(MACRO, ptr_in_line, 4) == 0) {
                read_string(macro_name, ptr_in_line + 4);
                macro_content = create_char_list();
                add_to_string_clist_table(macrosTable, list_to_string(macro_name), macro_content);
            } else {
                char *macro_name_array;
                read_string(macro_name, ptr_in_line);
                macro_name_array = list_to_string(macro_name);
                macro_content = get_from_string_clist_table(macrosTable, macro_name_array);
                if(macro_content != NULL) {
                    char *content_array = list_to_string(macro_content);
                    fputs(content_array, source_file);
                    free(content_array);
                } else {
                    fputs(line, source_file);
                }
                clear_list(macro_name);
                free(macro_name_array);
            }
        }
    }
    printf("\n");
    free_clist_table(macrosTable);
    free_list(macro_name);
    return 0;
}