#include <stdio.h>
#include "list.h"
#include "instruction_line.h"
#include "constants.h"
#include "error.h"
#include "parse.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void handle_data();
void handle_operation(char * ptr_in_line, int line_index, plist instruciton_image);
void fill_missing_labels_addresses();
void build_image(FILE * source_file, plist instruction_image, plist data_image);
char * get_next_param(char *ptr_in_line, clist param, Bool *read_param, int line_index);


void assemble(FILE * source_file) {
    plist insturction_image = create_plist();
    plist data_image = create_plist();
    /*symbols_table*/
    /*Missing labels indexes table*/
    build_image(source_file, insturction_image, data_image);
    fill_missing_labels_addresses();
    int i = 0;
    for (; i < get_plist_length(insturction_image); i++) {
        print_i_line(get_pointer_from_list(insturction_image, i));
    }
    free_plist(insturction_image);
    free_plist(data_image);
    printf("\n");
}

void build_image(FILE * source_file, plist instruction_image, plist data_image) {
    char line[MAX_LINE_SIZE];
    char *ptr_in_line;
    int i = 0;
    while(fgets(line, MAX_LINE_SIZE, source_file) != NULL) {
        i++;
        ptr_in_line = read_label(line, i);
        if(is_line_comment_or_blank(ptr_in_line)) {
            continue;
        }
        if(is_line_data_instruction(ptr_in_line)) {
            handle_data();
        } else {
            handle_operation(ptr_in_line, i, instruction_image);
        }
        
    }
}

void handle_data() {

}

void handle_operation(char * ptr_in_line, int line_index, plist instruciton_image) {
    i_line first_line = create_iline();
    i_line second_line = NULL;
    i_line third_line = NULL;
    operation op;
    Bool read_param;
    clist param = create_clist();
    short expected_params_to_read;

    printf("%d\t: %s", line_index, ptr_in_line);

    ptr_in_line = read_operation(ptr_in_line, &op, line_index);
    ptr_in_line = skip_spaces(ptr_in_line);
    set_operation(first_line, op);
    expected_params_to_read = get_params_to_read(op);
    if(0 < expected_params_to_read) {
        ptr_in_line = skip_spaces(ptr_in_line);
        while (*ptr_in_line != '\0' && !isspace(*ptr_in_line) && *ptr_in_line != ',') {
            append_char(param, *ptr_in_line++);
            read_param = True;
        }
        printf("Param 1: '%s'\n", list_to_string(param));
        if(get_char_from_list(param, 0) == '@') {
            unsigned short reg = get_char_from_list(param, 2) - '0';
            if (reg < 0 || 7 < reg || get_length(param) > 3 || get_char_from_list(param, 1) != 'r') {
                PRINT_ERROR_WITH_INDEX("unknown register", line_index);
                return;
            } 
            register_name reg_ = reg;
            set_source_address_type(first_line, IMM_REG_ADDR);
            second_line = create_iline();
            set_register_source_operand(second_line, reg_);
    }
    }
    
    
    if(1 < expected_params_to_read) {
        ptr_in_line =  get_next_param(ptr_in_line, param, &read_param, line_index);
        printf("Param 2: '%s'\n", list_to_string(param));
    }

    check_for_extra_text(ptr_in_line, line_index);
    append_pointer(instruciton_image, first_line);
    append_pointer_if_not_null(instruciton_image, second_line);
    append_pointer_if_not_null(instruciton_image, third_line);
}

void fill_missing_labels_addresses() {

}





