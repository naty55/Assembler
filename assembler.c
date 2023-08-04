#include "assembler.h"
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

void assemble(char * filename) {
    char * am_filename = concat(filename, ".am");
    FILE * am_file = fopen(am_filename, "r");
    if(am_file != NULL) {
        build(am_file, filename);
        fclose(am_file);
    } else {
        FILE_ERROR(am_filename);
    }
    free(am_filename);
}

void build(FILE * am_file, char * filename) {
    plist instruction_image = create_plist();
    plist data_image = create_plist();
    ptable symbols_table = create_ptable();
    ptable missing_symbols = create_ptable();
    plist entries = create_plist();
    plist externals = create_plist();
    Bool error = False;
    build_image(am_file, instruction_image, data_image, symbols_table, missing_symbols, entries, externals, &error);
    fill_missing_labels_addresses(missing_symbols, symbols_table, get_plist_length(instruction_image), &error);
    validate_entries(entries, symbols_table, &error);
    write_result_files(instruction_image, data_image, symbols_table, missing_symbols, externals, entries, filename, &error);
    free_objects(instruction_image, data_image, symbols_table, entries, externals, missing_symbols);
}

void build_image(FILE * source_file, plist instruction_image, plist data_image, ptable symbols_table, ptable missing_symbols, plist entries, plist externals, Bool *error) {
    char line[MAX_LINE_SIZE];
    char *ptr_in_line;
    int line_index = 0;
    while(fgets(line, MAX_LINE_SIZE, source_file) != NULL) {
        symbol sym = NULL;
        line_index++;
        DEBUG_LINE(line, line_index);
        ptr_in_line = read_label(line, line_index, symbols_table, &sym, get_plist_length(instruction_image), error);
        if(is_line_comment_or_blank(ptr_in_line)) {
            continue;
        }
        if(is_line_data_instruction(ptr_in_line)) {
            handle_data(ptr_in_line, line_index, data_image, symbols_table, sym, entries, externals, error);
        } else {
            handle_operation(ptr_in_line, line_index, instruction_image, symbols_table, missing_symbols, error);
        }
        
    }
}

void handle_data(char * ptr_in_line, int line_index, plist data_image, ptable symbols_table, symbol sym, plist entries, plist externals, Bool *error) {
    data_instruction inst;
    ptr_in_line = read_data_instruction(ptr_in_line, &inst, line_index, error);
    IF_ERROR_RETURN(error);
    if(sym == NULL && (inst == STRING || inst == DATA)) {
        WARN("inaccessible data", line_index);
    }
    if(sym != NULL && (inst == EXTERN || inst == ENTRY)) {
        WARN("redundent label", line_index);
    }
    
    switch (inst)
    {
    case STRING:
        handle_string(ptr_in_line, line_index, sym, data_image, error);
        break;
    case DATA:
        if(sym != NULL) {
            symbol_set_offset(sym, get_plist_length(data_image));
            symbol_set_is_data(sym, True);
            symbol_set_is_set(sym, False);
        }
        read_data(ptr_in_line, line_index, data_image, error);
        break;
    case EXTERN:
        read_externals(ptr_in_line, symbols_table, line_index, externals, error);
        break;
    case ENTRY:
        read_entries(ptr_in_line, entries, line_index, error);
        break;
    }
}

void handle_string(char * ptr_in_line, int line_index, symbol sym, plist data_image, Bool * error) {
    int i;
    clist str = create_clist();
    if(sym != NULL) {    
        symbol_set_offset(sym, get_plist_length(data_image));
        symbol_set_is_data(sym, True);
        symbol_set_is_set(sym, False);
    }
    read_string(ptr_in_line, line_index, str, error);
    IF_ERROR_RETURN(error);
    for (i = 0; i < get_length(str); i++) {
        i_line data_line = create_iline(get_plist_length(data_image));
        set_char(data_line, get_char_from_list(str, i));
        plist_append(data_image, data_line);
    }
    plist_append(data_image, create_iline(get_plist_length(data_image)));
    free(str);
}

void handle_operation(char * ptr_in_line, int line_index, plist instruciton_image, ptable symbols_table, ptable missing_symbols, Bool * error) {
    i_line first_line = create_iline(get_plist_length(instruciton_image) + IMAGE_OFFSET_SIZE);
    i_line second_line = NULL;
    i_line third_line = NULL;
    Bool current_line_has_error = False;
    operation op;
    Bool read_param;
    clist param1 = create_clist();
    address_type param1_type;
    int param1_data;
    clist param2 = create_clist();
    address_type param2_type;
    int param2_data;
    short expected_params_to_read;

    ptr_in_line = read_operation(ptr_in_line, &op, line_index, error);
    ptr_in_line = skip_spaces(ptr_in_line);
    expected_params_to_read = get_params_to_read(op);
    if(0 < expected_params_to_read) {
        ptr_in_line = read_next_param(ptr_in_line, param1, &read_param);
        DEBUG_1PARAM_STR("Param 1:", list_to_string(param1));
        param1_type = validate_param(param1, &param1_data, line_index, symbols_table, error);
    }

    if(1 < expected_params_to_read) {
        ptr_in_line = get_next_param(ptr_in_line, param2, &read_param, line_index, error);
        DEBUG_1PARAM_STR("Param 2:", list_to_string(param2));
        param2_type = validate_param(param2, &param2_data, line_index, symbols_table, error);
    }
    
    check_for_extra_text(ptr_in_line, line_index, error);
    *error = *error || current_line_has_error;
    IF_ERROR_RETURN(&current_line_has_error);
    
    set_operation(first_line, op);
    if(expected_params_to_read == 1) {
        if(!validate_op_and_target_param(op, param1_type)) {
            HANDLE_ERROR("incorrect param type", line_index, &current_line_has_error);
        }
        set_target_address_type(first_line, param1_type);
        second_line = create_iline(get_plist_length(instruciton_image) + 1 + IMAGE_OFFSET_SIZE);
        handle_param(param1, param1_data, param1_type, second_line, True, missing_symbols, line_index);
    
    }
    if(expected_params_to_read == 2) {
        if(!validate_op_and_source_param(op, param1_type)) {
            HANDLE_ERROR("incorrect param type", line_index, &current_line_has_error);
        }
        if(!validate_op_and_target_param(op, param2_type)) {
            HANDLE_ERROR("incorrect param type", line_index, &current_line_has_error);
        }
        set_source_address_type(first_line, param1_type);
        set_target_address_type(first_line, param2_type);
        if(param1_type == param2_type && param1_type == IMM_REG_ADDR) {
            second_line = create_iline(get_plist_length(instruciton_image) + 1 + IMAGE_OFFSET_SIZE);
            handle_param(param1, param1_data, param1_type, second_line, False, missing_symbols, line_index);
            handle_param(param2, param2_data, param2_type, second_line, True, missing_symbols, line_index);
        } else {
            second_line = create_iline(get_plist_length(instruciton_image) + 1 + IMAGE_OFFSET_SIZE);
            third_line  = create_iline(get_plist_length(instruciton_image) + 2 + IMAGE_OFFSET_SIZE);
            handle_param(param1, param1_data, param1_type, second_line, False, missing_symbols, line_index);
            handle_param(param2, param2_data, param2_type, third_line, True, missing_symbols, line_index);
        }
    }

    plist_append(instruciton_image, first_line);
    plist_append_if_not_null(instruciton_image, second_line);
    plist_append_if_not_null(instruciton_image, third_line);

}

void handle_param(clist param, int param_data, address_type param_type, i_line line, Bool is_target, ptable missing_symbols, int line_index) {
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
        if(param_data < -512 || 511 < param_data) {
            WARN("data overflow, will set data to 0", line_index);
        }
        set_data(line, param_data);
        break;
    }

}
void fill_missing_labels_addresses(ptable missing_symbols, ptable symbols_table, unsigned int instruction_image_size, Bool *error) {
    int i;
    plist keys;
    IF_ERROR_RETURN(error);

    keys = ptable_get_keys(missing_symbols);
    for (i = 0; i < get_plist_length(keys); i++) {
        char * symbol_name = get_pointer_from_list(keys, i);
        symbol sym = ptable_get(symbols_table, symbol_name);
        if(sym == NULL) {
            HANDLE_ERROR_ONE_PARAM("Can't find symbol ", symbol_name, -1, error);
        } else {
            plist lines = ptable_get(missing_symbols, symbol_name);
            int j = 0;
            for(; j < get_plist_length(lines); j++) {
                i_line line = get_pointer_from_list(lines, j);
                encoding sym_encoding = symbol_get_encoding(sym);
                unsigned int sym_address = symbol_get_offset(sym);
                Bool is_data = symbol_is_data(sym);
                Bool is_set  = symbol_is_set(sym);
                if(is_data && !is_set) {
                    sym_address += instruction_image_size + IMAGE_OFFSET_SIZE;
                    symbol_set_offset(sym, sym_address);
                    symbol_set_is_set(sym, True);
                }
                set_encoding(line, sym_encoding);
                set_label_address(line, sym_address);
                DEBUG_2PARAM("Setting label address label:", symbol_name, sym_address);
            }
            
        }
    }
    free_plist(keys);
}

void validate_entries(plist entries, ptable symbols_table, Bool * error) {
    int i;
    for(i=0; i < get_plist_length(entries); i++) {
        char * entry = get_pointer_from_list(entries, i);
        symbol sym = ptable_get(symbols_table, entry);
        if(sym != NULL) {
            if(symbol_get_encoding(sym) == E) {
                HANDLE_ERROR_ONE_PARAM("entry label can't be external, entry: ", entry, -1, error);
            }
        } else {
            HANDLE_ERROR_ONE_PARAM("entry label is not found, entry: ", entry, -1, error);
        }
    } 
}

void free_objects(plist instruction_image, plist data_image, ptable symbols_table, plist entries, plist externals, ptable missing_symbols) {
    free_plist(instruction_image);
    free_plist(data_image);
    free_ptable(symbols_table, free);
    free_plist(entries);
    free_plist(externals);
    free_ptable(missing_symbols, free);

}