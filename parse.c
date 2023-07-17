#include "parse.h"
#include "error.h"
#include "util.h"
#include "list.h"
#include "hashmap.h"
#include "error.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

Bool is_line_comment_or_blank(char * ptr_in_line) {
    return (Bool)(*ptr_in_line == ';' || *ptr_in_line == '\0');
}

Bool is_line_data_instruction(char * ptr_in_line) {
    return (Bool)(*ptr_in_line == '.');
}

char * read_operation(char * ptr_in_line, operation * op, int line_index) {
    if(strncmp("mov", ptr_in_line, 3) == 0) {
        *op = MOV;
    } else if(strncmp("cmp", ptr_in_line, 3) == 0) {
        *op = CMP;
    } else if(strncmp("add", ptr_in_line, 3) == 0) {
        *op = ADD;
    } else if(strncmp("sub", ptr_in_line, 3) == 0) {
        *op = SUB;
    } else if(strncmp("not", ptr_in_line, 3) == 0) {
        *op = NOT;
    } else if(strncmp("clr", ptr_in_line, 3) == 0) {
        *op = CLR;
    } else if(strncmp("lea", ptr_in_line, 3) == 0) {
        *op = LEA;
    } else if(strncmp("inc", ptr_in_line, 3) == 0) {
        *op = INC;
    } else if(strncmp("dec", ptr_in_line, 3) == 0) {
        *op = DEC;
    } else if(strncmp("jmp", ptr_in_line, 3) == 0) {
        *op = JMP;
    } else if(strncmp("bne", ptr_in_line, 3) == 0) {
        *op = BNE;
    } else if(strncmp("red", ptr_in_line, 3) == 0) {
        *op = RED;
    } else if(strncmp("prn", ptr_in_line, 3) == 0) {
        *op = PRN;
    } else if(strncmp("jsr", ptr_in_line, 3) == 0) {
        *op = JSR;
    } else if(strncmp("rts", ptr_in_line, 3) == 0) {
        *op = RTS;
    } else if(strncmp("stop", ptr_in_line, 4) == 0) {
        ptr_in_line++;
        *op = STP;
    } else {
        PRINT_ERROR_WITH_INDEX("unkonwn operation", line_index);
    }
    ptr_in_line += 3;
    if(!isspace(*ptr_in_line)) {
        PRINT_ERROR_WITH_INDEX("unknown operation", line_index);
    }
    return ptr_in_line;
}

char * read_label(char *ptr_in_line ,int line_index, symbol_table symbols_table, int image_index) {
    char * label;
    ptr_in_line = skip_spaces(ptr_in_line);
    label = ptr_in_line;
    if((ptr_in_line = strchr(ptr_in_line, ':')) != NULL) {
        if(ptr_in_line - label >= 31) {
            PRINT_ERROR_WITH_INDEX("too long label name", line_index);
        } else if (ptr_in_line - label == 0) {
            PRINT_ERROR_WITH_INDEX("label name must be at least of size 1", line_index);
        }
        else {
            *ptr_in_line = 0;
            ptr_in_line = skip_spaces(ptr_in_line + 1);
            add_to_int_table(symbols_table, label, 100 + image_index);
            printf("Found Label : %s\n", label);
            printf("Label location: %d\n", get_from_int_table(symbols_table, label));
        }
    } else {
        ptr_in_line = label;
    }
    return ptr_in_line;
}

char * get_next_param(char *ptr_in_line, clist param, Bool *read_param, int line_index) {
    clear_clist(param);
    *read_param = False;
    ptr_in_line = skip_spaces(ptr_in_line);
    if(*ptr_in_line++ != ',') {
        PRINT_ERROR_WITH_INDEX("Missing comma between params", line_index);
        return ptr_in_line;
    }
    ptr_in_line = skip_spaces(ptr_in_line);
    while (*ptr_in_line != '\0' && !isspace(*ptr_in_line) && *ptr_in_line != ',') {
        append_char(param, *ptr_in_line++);
        *read_param = True;
    }
        return ptr_in_line;
}

void check_for_extra_text(char *ptr_in_line, int line_index) {
    while(*ptr_in_line != '\0') { 
        if(!isspace(*ptr_in_line++)) {
            PRINT_ERROR_WITH_INDEX("unidentified text after end of line", line_index);
            return;
        }
    }
}

address_type validate_param(clist param, int line_index, symbol_table symbols_table) {
    char * param_str;
    if(get_char_from_list(param, 0) == '@') {
        unsigned short reg = get_char_from_list(param, 2) - '0';
        if (reg < 0 || 7 < reg || get_length(param) > 3 || get_char_from_list(param, 1) != 'r') {
            PRINT_ERROR_WITH_INDEX("unknown register", line_index);
            return IMM_REG_ADDR;
        }
        return IMM_REG_ADDR;
    }
     param_str = list_to_string(param);
    if(is_string_number(param_str)) {
        return ABS_ADDR;
    }
    if(is_param_label(param)) {
        return IMM_ADDR;
    }
    PRINT_ERROR_WITH_INDEX("unknown parameter type", line_index);
    free(param_str);
    return ABS_ADDR;
}

Bool is_param_label(clist param) {
    if(get_length(param) >= 32) {
        return False;
    }
    if(isalpha(get_char_from_list(param, 0))) {
        return True;
    }
    return False;
}