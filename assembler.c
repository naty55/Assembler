#include <stdio.h>
#include "list.h"
#include "hashmap.h"
#include "instruction_line.h"
#include "constants.h"
#include "error.h"
#include "parse.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void handle_operation(char * ptr_in_line, int line_index, plist instruciton_image, ptable symbols_table);
void fill_missing_labels_addresses();
void build_image(FILE * source_file, plist instruction_image, plist data_image, ptable symbols_table);
char * get_next_param(char *ptr_in_line, clist param, Bool *read_param, int line_index);
void handle_param(clist param, address_type param_type, i_line line, Bool is_target);
void handle_data(char * ptr_in_line, int line_index, plist data_image, ptable symbols_table, symbol sym);
void print_image(plist instruction_image, plist data_image);

void assemble(FILE * source_file) {
    plist insturction_image = create_plist();
    plist data_image = create_plist();
    ptable symbols_table = create_ptable();
    build_image(source_file, insturction_image, data_image, symbols_table);
    fill_missing_labels_addresses();
    print_image(insturction_image, data_image);
    free_plist(insturction_image);
    free_plist(data_image);
    free_ptable(symbols_table);
}

void build_image(FILE * source_file, plist instruction_image, plist data_image, ptable symbols_table) {
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
            handle_data(ptr_in_line, line_index, data_image, symbols_table, sym);
        } else {
            handle_operation(ptr_in_line, line_index, instruction_image, symbols_table);
            if(sym != NULL) {
                symbol_set_encoding(sym, A);
            }
            
        }
        
    }
}

void handle_data(char * ptr_in_line, int line_index, plist data_image, ptable symbols_table, symbol sym) {
    data_instruction inst;
    if(sym == NULL) {
        PRINT_ERROR_WITH_INDEX("INTERNAL ERROR sym==NULL", line_index); /* TODO: See open question issue #3*/
    }
    ptr_in_line = read_data_instruction(ptr_in_line, &inst, line_index);
    switch (inst)
    {
    case STRING:
        symbol_set_offset(sym, get_plist_length(data_image));
        read_string(ptr_in_line, line_index, data_image);
        break;
    case DATA:
        symbol_set_offset(sym, get_plist_length(data_image));
        read_data(ptr_in_line, line_index, data_image);
        break;
    case EXTERN:
        symbol_set_encoding(sym, E);
        symbol_set_offset(sym, 0);
        break;
    case ENTRY:
        break;
    }
}

void handle_operation(char * ptr_in_line, int line_index, plist instruciton_image, ptable symbols_table) {
    i_line first_line = create_iline();
    i_line second_line = NULL;
    i_line third_line = NULL;
    operation op;
    Bool read_param;
    clist param1 = create_clist();
    address_type param1_type;
    clist param2 = create_clist();
    address_type param2_type;
    short expected_params_to_read;

    ptr_in_line = read_operation(ptr_in_line, &op, line_index);
    ptr_in_line = skip_spaces(ptr_in_line);
    set_operation(first_line, op);
    expected_params_to_read = get_params_to_read(op);
    if(0 < expected_params_to_read) {
        ptr_in_line = read_next_param(ptr_in_line, param1, &read_param);
        printf("Param 1: '%s'\n", list_to_string(param1));
        param1_type = validate_param(param1, line_index, symbols_table);
    }

    if(1 < expected_params_to_read) {
        ptr_in_line =  get_next_param(ptr_in_line, param2, &read_param, line_index);
        printf("Param 2: '%s'\n", list_to_string(param2));
        param2_type = validate_param(param2, line_index, symbols_table);
    }

    if(expected_params_to_read == 1) {
        set_target_address_type(first_line, param1_type);
        second_line = create_iline();
        handle_param(param1, param1_type, second_line, True);
    
    }
    if(expected_params_to_read == 2) {
        set_source_address_type(first_line, param1_type);
        set_target_address_type(first_line, param2_type);
        if(param1_type == param2_type && param1_type == IMM_REG_ADDR) {
            second_line = create_iline();
            handle_param(param1, param1_type, second_line, False);
            handle_param(param2, param2_type, second_line, True);
        } else {
            second_line = create_iline();
            third_line = create_iline();
            handle_param(param1, param1_type, second_line, False);
            handle_param(param2, param2_type, third_line, True);
        }
    }

    print_i_line(first_line);
    print_i_line(second_line);
    print_i_line(third_line);
    check_for_extra_text(ptr_in_line, line_index);
    append_pointer(instruciton_image, first_line);
    append_pointer_if_not_null(instruciton_image, second_line);
    append_pointer_if_not_null(instruciton_image, third_line);

}

void handle_param(clist param, address_type param_type, i_line line, Bool is_target) {
    switch (param_type)
    {
    case IMM_REG_ADDR:
        if(is_target) {
            set_register_target_operand(line, get_char_from_list(param, 2) - '0');
        } else {
            set_register_source_operand(line, get_char_from_list(param, 2) - '0');
        }
        break;
    case IMM_ADDR: /* Will handle it later. */
        break;
    case ABS_ADDR:
        set_data(line, -5);
        break;
    }

}
void fill_missing_labels_addresses() {

}

void print_image(plist instruction_image, plist data_image) {
    int i = 0;
    printf("============================\n");
    printf("=========== RESULT =========\n");
    printf("============================\n");
    printf("====== %ld\t===== %ld\t====\n", get_plist_length(instruction_image), get_plist_length(data_image));
    printf("============================\n");
    printf("============================\n");
    for (; i < get_plist_length(instruction_image); i++) {
        print_iline_in_base64(get_pointer_from_list(instruction_image, i));
    }
    for (i = 0; i < get_plist_length(data_image); i++) {
        print_iline_in_base64(get_pointer_from_list(data_image, i));
    }
}
