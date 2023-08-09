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
    Bool is_successful = True;
    FILE * am_file;
    FILE * as_file;
    char * as_filename = concat(filename, ".as");
    char * am_filename = concat(filename, ".am");
    as_file = fopen(as_filename, "r");
    if(as_file == NULL) {
        FILE_ERROR(as_filename);
        free(as_filename);
        free(am_filename);
        return False;   
    }
    am_file = fopen(am_filename, "w");
    if(am_file == NULL) {
        FILE_ERROR(as_filename);
        free(as_filename);
        free(am_filename);
        return False;
    }
    is_successful = remove_macros(as_file, am_file);
    if(!is_successful) {
        remove(am_filename);
    }
    free(as_filename);
    free(am_filename);
    fclose(as_file);
    fclose(am_file);
    return is_successful;
}

Bool remove_macros(FILE *input_file, FILE* source_file) {
    int line_index = 1;
    char line[MAX_LINE_SIZE];
    char *ptr_in_line;
    clist macro_name = create_clist(); /* If we are reading macro - it's not empty */
    clist macro_content;
    ptable macros_table = create_ptable();
    line[MAX_LINE_SIZE - 1] = 0;
    while(fgets(line, MAX_LINE_SIZE + 1, input_file) != NULL) {
        if(line[MAX_LINE_SIZE - 1] != 0) {
            ERROR("too long line", line_index);
            ptable_free(macros_table, free);
            clist_free(macro_name);
            return False;
        }
        ptr_in_line = skip_spaces(line);
        if(!clist_is_empty(macro_name)) { /* We are reading macro - so read its content */
            read_macro_content(line, macro_name, macro_content);
            continue;
        }
        
        if(strncmp(MACRO, ptr_in_line, 4) == 0) { /* Found macro declaration */
            if(!read_macro_name(ptr_in_line + 4, macro_name, &macro_content, macros_table, line_index)) {
                ptable_free(macros_table, free);
                clist_free(macro_name);
                return False;
            }
            continue;
        } 
        write_line(ptr_in_line, macro_name, macro_content, macros_table, line, source_file);
        line_index++;  
    }
    
    ptable_free(macros_table, (freeFunction)clist_free);
    clist_free(macro_name);
    return True;
}

void read_macro_content(char * ptr_in_line, clist macro_name, clist macro_content) {
    if(strncmp(ENDMACRO, ptr_in_line, 7) == 0) {
        clist_clear(macro_name);
    } else {
        clist_append_chars(macro_content, ptr_in_line);
    }
}

Bool read_macro_name(char * ptr_in_line, clist macro_name, clist * macro_content, ptable macros_table, int line_index) {
    char *macro_name_array;
    clist_read_string(macro_name, ptr_in_line);
    macro_name_array = clist_to_string(macro_name);
    if(is_keyword(macro_name_array)) {
        ERROR("macro name is a keyword", line_index);
        free(macro_name_array);
        return False;
    }
    *macro_content = create_clist();
    DEBUG_1PARAM_STR("found macro: ", macro_name_array);
    ptable_insert(macros_table, macro_name_array, *macro_content);
    free(macro_name_array);
    return True;
}

void write_line(char * ptr_in_line, clist macro_name, clist macro_content, ptable macros_table, char line[], FILE * source_file) {
    char *macro_name_array;
    clist_read_string(macro_name, ptr_in_line);
    macro_name_array = clist_to_string(macro_name);
    macro_content = ptable_get(macros_table, macro_name_array);
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