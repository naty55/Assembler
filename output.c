#include "output.h"
#include "util.h"
#include "list.h"
#include "error.h"
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
    if(!should_write_ext_file(externals, missing_symbols)) {
        return True;
    }
    
    ext_filename = concat(filename, ".ext");
    INFO_1PARAM_STR("Write externals file", ext_filename);

    ext_file = fopen(ext_filename, "w");
    for (i = 0; i < plist_get_length(externals); i++) {
        char * label = plist_get(externals, i);
        plist lines = ptable_get(missing_symbols, label);
        if(lines == NULL) {
            continue;
        }
        for (j = 0; j < plist_get_length(lines); j++) {
            i_line line = plist_get(lines, j);
            fprintf(ext_file, "%s\t%ld\n", label, i_line_get_binary_line_index(line));
        }
    }
    fclose(ext_file);
    free(ext_filename);
    return True;
}
Bool write_ent(ptable entries, ptable symbols_table, char *filename) {
    plist keys = ptable_get_keys(entries);
    int i;
    char * ent_filename;
    FILE * ent_file;

    if(plist_get_length(keys) == 0) {
        plist_free_all(keys);
        return True;
    }

    i = 0;
    ent_filename = concat(filename, ".ent");
    INFO_1PARAM_STR("Write entries file", ent_filename);

    ent_file = fopen(ent_filename, "w");
    for (;i < plist_get_length(keys); i++) {
        char * label = plist_get(keys, i);
        symbol sym = ptable_get(symbols_table, label);
        fprintf(ent_file, "%s\t%d\n", label, symbol_get_address(sym));
    }
    fclose(ent_file);
    free(ent_filename);
    plist_free_all(keys);
    return True;
}
Bool write_obj(plist inst_iamge, plist data_image, char *filename) {
    char * obj_filename = concat(filename, ".ob");
    int i = 0;
    char data[2];
    FILE * obj_file = fopen(obj_filename, "w");
    INFO_1PARAM_STR("Write object file", obj_filename);
    fprintf(obj_file, "%ld\t%ld\n", plist_get_length(inst_iamge), plist_get_length(data_image));
    for (; i < plist_get_length(inst_iamge); i++) {
        convertToBase64(i_line_get_data(plist_get(inst_iamge, i)), data);
        if(fprintf(obj_file, "%s\n", data) < 0) {
            FATAL_ERROR("writing to file failed");
        }
    }
    for (i=0; i < plist_get_length(data_image); i++) {
        convertToBase64(i_line_get_data(plist_get(data_image, i)), data);
        fprintf(obj_file, "%s\n", data);
    }
    free(obj_filename);
    fclose(obj_file);
    return True;
}
void write_result_files(plist inst_image, plist data_image, ptable symbols_table, ptable missing_symbols, plist externals, ptable entries, char * filename, Bool *error) {
    IF_ERROR_RETURN(error);
    write_ext(externals, missing_symbols, filename);
    write_ent(entries, symbols_table, filename);
    write_obj(inst_image, data_image, filename);
}

Bool should_write_ext_file(plist externals, ptable missing_symbols) {
    int i;
    for (i = 0; i < plist_get_length(externals); i++) {
        char * label = plist_get(externals, i);
        plist lines = ptable_get(missing_symbols, label);
        if(lines != NULL) {
            return True;
        } 
    }
    return False;
}