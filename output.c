#include "util.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruction_line.h"
#include "hashmap.h"
#include "symbol.h"

Bool write_ext(plist externals, ptable missing_symbols, char *filename) {
    int i,j;
    char * ext_filename;
    FILE * ext_file;
    if(get_plist_length(externals) == 0) {
        return True;
    }

    ext_filename = concat(filename, ".ext");
    ext_file = fopen(ext_filename, "w");
    
    for (i = 0; i < get_plist_length(externals); i++) {
        char * label = get_pointer_from_list(externals, i);
        plist lines = ptable_get(missing_symbols, label);
        for (j = 0; j < get_plist_length(lines); j++) {
            i_line line = get_pointer_from_list(lines, j);
            fprintf(ext_file, "%s\t%ld\n", label, i_line_get_binary_line_index(line));
        }
        
    }
    fclose(ext_file);
    free(ext_filename);
    return True;
}
Bool write_ent(plist entries, ptable symbols_table, char *filename) {
    int i;
    char * ent_filename;
    FILE * ent_file;

    if(get_plist_length(entries) == 0) {
        return True;
    }

    i = 0;
    ent_filename = concat(filename, ".ent");
    ent_file = fopen(ent_filename, "w");
    
    for (;i < get_plist_length(entries); i++) {
        char * label = get_pointer_from_list(entries, i);
        symbol sym = ptable_get(symbols_table, label);
        fprintf(ent_file, "%s\t%d\n", label, symbol_get_offset(sym));
    }
    fclose(ent_file);
    free(ent_filename);
    return True;
}
Bool write_obj(plist inst_iamge, plist data_image, char *filename) {
    char * obj_filename = concat(filename, ".obj");
    int i = 0;
    char data[2];
    FILE * obj_file = fopen(obj_filename, "w");
    fprintf(obj_file, "%ld\t%ld\n", get_plist_length(inst_iamge), get_plist_length(data_image));
    for (; i < get_plist_length(inst_iamge); i++) {
        convertToBase64(i_line_get_data(get_pointer_from_list(inst_iamge, i)), data);
        fprintf(obj_file, "%s\n", data);
    }
    for (i=0; i < get_plist_length(data_image); i++) {
        convertToBase64(i_line_get_data(get_pointer_from_list(data_image, i)), data);
        fprintf(obj_file, "%s\n", data);
    }
    free(obj_filename);
    fclose(obj_file);
    return True;
}
Bool write_result_files(plist inst_image, plist data_image, ptable symbols_table, ptable missing_symbols, plist externals, plist entries, char * filename) {
    return write_ext(externals, missing_symbols, filename) && 
           write_ent(entries, symbols_table, filename) && 
           write_obj(inst_image, data_image, filename);
}