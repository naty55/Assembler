#include "util.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruction_line.h"
#include "hashmap.h"
#include "symbol.h"

Bool write_ext(plist externals, ptable symbols_table, char *filename) {
    return True;
}
Bool write_ent(plist entries, ptable symbols_table, char *filename) {
    if(get_plist_length(entries) == 0) {
        return True;
    }
    int i = 0;
    char * ent_filename = concat(filename, ".ent");
    FILE * ent_file = fopen(ent_filename, "w");
    
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
Bool write_result_files(plist inst_image, plist data_image, ptable symbols_table, plist externals, plist entries, char * filename) {
    return write_ext(externals, symbols_table, filename) && 
           write_ent(entries, symbols_table, filename) && 
           write_obj(inst_image, data_image, filename);
}