#include <stdio.h>
#include "list.h"
#include "hashmap.h"
Bool pre_assemble(char * filename);
Bool remove_macros(FILE *input_file, FILE* source_file);
Bool read_macro_name(char * ptr_in_line, clist macro_name, clist * macro_content, ptable macros_table, int line_index);
void read_macro_content(char * ptr_in_line, clist macro_name, clist macro_content);
void write_line(char * ptr_in_line, clist macro_name, clist macro_content, ptable macros_table, char line[], FILE * source_file);