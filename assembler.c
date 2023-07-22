#include <stdio.h>
#include "list.h"
#include "output.h"
#include "hashmap.h"
#include "instruction_line.h"
#include "constants.h"
#include "error.h"
#include "parse.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void handle_operation(char * ptr_in_line, int line_index, plist instruciton_image, ptable symbols_table, ptable missing_symbols);
void fill_missing_labels_addresses(ptable missing_symbols, ptable symbols_table, unsigned int instruction_image_size);
void build_image(FILE * source_file, plist instruction_image, plist data_image, ptable symbols_table, ptable missing_symbols, plist entries, plist externals);
char * get_next_param(char *ptr_in_line, clist param, Bool *read_param, int line_index);
void handle_param(clist param, int param_data, address_type param_type, i_line line, Bool is_target, ptable missing_symbols);
void handle_data(char * ptr_in_line, int line_index, plist data_image, ptable symbols_table, symbol sym, plist entries, plist externals);

void assemble(FILE * source_file, char * filename) {
    plist instruction_image = create_plist();
    plist data_image = create_plist();
    ptable symbols_table = create_ptable();
    ptable missing_symbols = create_ptable();
    plist entries = create_plist();
    plist externals = create_plist();
    build_image(source_file, instruction_image, data_image, symbols_table, missing_symbols, entries, externals);
    fill_missing_labels_addresses(missing_symbols, symbols_table, get_plist_length(instruction_image));
    write_result_files(instruction_image, data_image, symbols_table, missing_symbols, externals, entries, filename);
    free_plist(instruction_image);
    free_plist(data_image);
    free_ptable(symbols_table, free);
    free_ptable(missing_symbols, (freeFunction)free_plist);
    free_plist(entries);
    free_plist(externals);
}

void build_image(FILE * source_file, plist instruction_image, plist data_image, ptable symbols_table, ptable missing_symbols, plist entries, plist externals) {
    char line[MAX_LINE_SIZE];
    char *ptr_in_line;
    int line_index = 0;
    while(fgets(line, MAX_LINE_SIZE, source_file) != NULL) {
        symbol sym = NULL;
        line_index++;
        printf("%d\t: %s\n", line_index, line);
        ptr_in_line = read_label(line, line_index, symbols_table, &sym, get_plist_length(instruction_image));
        if(is_line_comment_or_blank(ptr_in_line)) {
            continue;
        }
        if(is_line_data_instruction(ptr_in_line)) {
            handle_data(ptr_in_line, line_index, data_image, symbols_table, sym, entries, externals);
        } else {
            handle_operation(ptr_in_line, line_index, instruction_image, symbols_table, missing_symbols);
        }
        
    }
}

void handle_data(char * ptr_in_line, int line_index, plist data_image, ptable symbols_table, symbol sym, plist entries, plist externals) {
    data_instruction inst;
    ptr_in_line = read_data_instruction(ptr_in_line, &inst, line_index);

    if(sym == NULL && inst != EXTERN && inst != ENTRY) {
        PRINT_ERROR_WITH_INDEX("INTERNAL ERROR sym==NULL", line_index); /* TODO: See open question issue #3*/
        return;
    }
    
    switch (inst)
    {
    case STRING:
        symbol_set_offset(sym, get_plist_length(data_image));
        symbol_set_is_data(sym, True);
        read_string(ptr_in_line, line_index, data_image);
        break;
    case DATA:
        symbol_set_offset(sym, get_plist_length(data_image));
        symbol_set_is_data(sym, True);
        read_data(ptr_in_line, line_index, data_image);
        break;
    case EXTERN:
        read_externals(ptr_in_line, symbols_table, line_index, externals);
        break;
    case ENTRY:
        read_entries(ptr_in_line, entries, line_index);
        break;
    }
}

void handle_operation(char * ptr_in_line, int line_index, plist instruciton_image, ptable symbols_table, ptable missing_symbols) {
    i_line first_line = create_iline(get_plist_length(instruciton_image) + IMAGE_OFFSET_SIZE);
    i_line second_line = NULL;
    i_line third_line = NULL;
    operation op;
    Bool read_param;
    clist param1 = create_clist();
    address_type param1_type;
    int param1_data;
    clist param2 = create_clist();
    address_type param2_type;
    int param2_data;
    short expected_params_to_read;

    ptr_in_line = read_operation(ptr_in_line, &op, line_index);
    ptr_in_line = skip_spaces(ptr_in_line);
    set_operation(first_line, op);
    expected_params_to_read = get_params_to_read(op);
    if(0 < expected_params_to_read) {
        ptr_in_line = read_next_param(ptr_in_line, param1, &read_param);
        printf("Param 1: '%s'\n", list_to_string(param1));
        param1_type = validate_param(param1, &param1_data, line_index, symbols_table);
    }

    if(1 < expected_params_to_read) {
        ptr_in_line =  get_next_param(ptr_in_line, param2, &read_param, line_index);
        printf("Param 2: '%s'\n", list_to_string(param2));
        param2_type = validate_param(param2, &param2_data, line_index, symbols_table);
    }

    if(expected_params_to_read == 1) {
        set_target_address_type(first_line, param1_type);
        second_line = create_iline(get_plist_length(instruciton_image) + 1 + IMAGE_OFFSET_SIZE);
        handle_param(param1, param1_data, param1_type, second_line, True, missing_symbols);
    
    }
    if(expected_params_to_read == 2) {
        set_source_address_type(first_line, param1_type);
        set_target_address_type(first_line, param2_type);
        if(param1_type == param2_type && param1_type == IMM_REG_ADDR) {
            second_line = create_iline(get_plist_length(instruciton_image) + 1 + IMAGE_OFFSET_SIZE);
            handle_param(param1, param1_data, param1_type, second_line, False, missing_symbols);
            handle_param(param2, param2_data, param2_type, second_line, True, missing_symbols);
        } else {
            second_line = create_iline(get_plist_length(instruciton_image) + 1 + IMAGE_OFFSET_SIZE);
            third_line  = create_iline(get_plist_length(instruciton_image) + 2 + IMAGE_OFFSET_SIZE);
            handle_param(param1, param1_data, param1_type, second_line, False, missing_symbols);
            handle_param(param2, param2_data, param2_type, third_line, True, missing_symbols);
        }
    }

    check_for_extra_text(ptr_in_line, line_index);
    plist_append(instruciton_image, first_line);
    plist_append_if_not_null(instruciton_image, second_line);
    plist_append_if_not_null(instruciton_image, third_line);

}

void handle_param(clist param, int param_data, address_type param_type, i_line line, Bool is_target, ptable missing_symbols) {
    switch (param_type)
    {
    case IMM_REG_ADDR:
        if(is_target) {
            set_register_target_operand(line, get_char_from_list(param, 2) - '0');
        } else {
            set_register_source_operand(line, get_char_from_list(param, 2) - '0');
        }
        break;
    case IMM_ADDR:  {
        char *param_str = list_to_string(param);
        plist lines = ptable_get(missing_symbols, param_str);
        if(lines == NULL) {
            lines = create_plist();
            ptable_insert(missing_symbols, param_str ,lines);
        }
        plist_append(lines, line);
        free(param_str);
    }
        break;
    case ABS_ADDR:
        set_data(line, param_data);
        break;
    }

}
void fill_missing_labels_addresses(ptable missing_symbols, ptable symbols_table, unsigned int instruction_image_size) {
    int i = 0;
    plist keys = ptable_get_keys(missing_symbols);
    for (; i < get_plist_length(keys); i++) {
        char * symbol_name = get_pointer_from_list(keys, i);
        symbol sym = ptable_get(symbols_table, symbol_name);
        if(sym == NULL) {
            PRINT_ERROR_WITH_INDEX("Can't find symbol", -1);
        } else {
            plist lines = ptable_get(missing_symbols, symbol_name);
            int j = 0;
            for(; j < get_plist_length(lines); j++) {
                i_line line = get_pointer_from_list(lines, j);
                encoding sym_encoding = symbol_get_encoding(sym);
                unsigned int sym_address = symbol_get_offset(sym);
                Bool is_data = symbol_is_data(sym);
                if(is_data) {
                    sym_address += instruction_image_size + IMAGE_OFFSET_SIZE;
                    symbol_set_offset(sym, sym_address);
                }
                set_encoding(line, sym_encoding);
                set_label_address(line, sym_address);
                printf("Setting label address label: '%s' address: %u\n", symbol_name, sym_address);
            }
            
        }
    }
    free_plist(keys);
}