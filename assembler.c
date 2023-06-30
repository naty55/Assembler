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

void handle_data();
void handle_operation(char * ptr_in_line, int line_index, plist instruciton_image, int_table symbols_table);
void fill_missing_labels_addresses();
void build_image(FILE * source_file, plist instruction_image, plist data_image, int_table symbols_table);
char * get_next_param(char *ptr_in_line, clist param, Bool *read_param, int line_index);


void assemble(FILE * source_file) {
    plist insturction_image = create_plist();
    plist data_image = create_plist();
    int_table symbols_table = create_int_table();
    build_image(source_file, insturction_image, data_image, symbols_table);
    fill_missing_labels_addresses();
    int i = 0;
    printf("============================\n");
    printf("=========== RESULT =========\n");
    printf("============================\n");
    for (; i < get_plist_length(insturction_image); i++) {
        print_iline_in_base64(get_pointer_from_list(insturction_image, i));
    }
    free_plist(insturction_image);
    free_plist(data_image);
    free_int_table(symbols_table);
    printf("\n");
}

void build_image(FILE * source_file, plist instruction_image, plist data_image, int_table symbols_table) {
    char line[MAX_LINE_SIZE];
    char *ptr_in_line;
    int i = 0;
    while(fgets(line, MAX_LINE_SIZE, source_file) != NULL) {
        i++;
        ptr_in_line = line;
        printf("%d\t: %s", i, ptr_in_line);
        ptr_in_line = read_label(line, i, symbols_table, get_plist_length(instruction_image));
        if(is_line_comment_or_blank(ptr_in_line)) {
            continue;
        }
        if(is_line_data_instruction(ptr_in_line)) {
            handle_data();
        } else {
            handle_operation(ptr_in_line, i, instruction_image, symbols_table);
        }
        
    }
}

void handle_data() {

}

void handle_operation(char * ptr_in_line, int line_index, plist instruciton_image, int_table symbols_table) {
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
        ptr_in_line = skip_spaces(ptr_in_line);
        while (*ptr_in_line != '\0' && !isspace(*ptr_in_line) && *ptr_in_line != ',') {
            append_char(param1, *ptr_in_line++);
            read_param = True;
        }
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
        switch (param1_type) {
        case IMM_REG_ADDR:
            set_register_target_operand(second_line, get_char_from_list(param1, 2) - '0');
            break;
        case ABS_ADDR:
            set_data(second_line, -5);
        default:
            break;
        }
    
    }
    if(expected_params_to_read == 2) {
        set_source_address_type(first_line, param1_type);
        set_target_address_type(first_line, param2_type);
        if(param1_type != param2_type) {
            second_line = create_iline();
            third_line = create_iline();
        } else {         
            second_line = create_iline();
            if(param1_type == IMM_REG_ADDR) {
                set_register_source_operand(second_line, get_char_from_list(param1, 2) - '0');
                set_register_target_operand(second_line, get_char_from_list(param2, 2) - '0');
            } else if(param1_type == ABS_ADDR) {
                third_line = create_iline();
                set_data(second_line, '3');
                set_data(third_line, '3');
            } else if(param1_type == IMM_ADDR) {
                third_line = create_iline();
            }
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

void fill_missing_labels_addresses() {

}


