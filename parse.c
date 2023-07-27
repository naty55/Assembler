#include "parse.h"
#include "error.h"
#include "util.h"
#include "list.h"
#include "instruction_line.h"
#include "hashmap.h"
#include "symbol.h"
#include "error.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

Bool is_line_comment_or_blank(char * ptr_in_line) {
    ptr_in_line = skip_spaces(ptr_in_line);
    return (Bool)(*ptr_in_line == ';' || *ptr_in_line == '\0');
}

Bool is_line_data_instruction(char * ptr_in_line) {
    ptr_in_line = skip_spaces(ptr_in_line);
    return (Bool)(*ptr_in_line == '.');
}

char * read_operation(char * ptr_in_line, operation * op, int line_index, Bool *error) {
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
        HANDLE_ERROR("unkonwn operation", line_index);
    }
    ptr_in_line += 3;
    if(!isspace(*ptr_in_line)) {
        HANDLE_ERROR("unknown operation", line_index);
    }
    return ptr_in_line;
}

char * read_label(char *ptr_in_line ,int line_index, ptable symbols_table, symbol* sym, unsigned int image_index, Bool *error) {
    char * label;
    ptr_in_line = skip_spaces(ptr_in_line);
    label = ptr_in_line;
    if((ptr_in_line = strchr(ptr_in_line, ':')) != NULL) {
        if(ptr_in_line - label >= 31) {
            HANDLE_ERROR("too long label name", line_index);
        } else if (ptr_in_line - label == 0) {
            HANDLE_ERROR("label name must be at least of size 1", line_index);
        }
        else {
            *ptr_in_line = 0;
            ptr_in_line = skip_spaces(ptr_in_line + 1);
            *sym = create_symbol();
            symbol_set_encoding(*sym, R);
            symbol_set_offset(*sym, IMAGE_OFFSET_SIZE + image_index);
            symbol_set_is_data(*sym, False);
            ptable_insert(symbols_table, label ,*sym);
            printf("Found Label : %s\n", label);
            printf("Label location: %d\n", symbol_get_offset(ptable_get(symbols_table, label)));
        }
    } else {
        ptr_in_line = label;
    }
    return ptr_in_line;
}

char * get_next_param(char *ptr_in_line, clist param, Bool *read_param, int line_index, Bool *error) {
    clear_clist(param);
    *read_param = False;
    ptr_in_line = skip_spaces(ptr_in_line);
    if(*ptr_in_line++ != ',') {
        HANDLE_ERROR("Missing comma between params", line_index);
        return ptr_in_line;
    }
    return read_next_param(ptr_in_line, param, read_param);
}

char * read_next_param(char * ptr_in_line, clist param, Bool *read_param) {
    ptr_in_line = skip_spaces(ptr_in_line);
    while (*ptr_in_line != '\0' && !isspace(*ptr_in_line) && *ptr_in_line != ',') {
        append_char(param, *ptr_in_line++);
        *read_param = True;
    }
    return ptr_in_line;
}

void check_for_extra_text(char *ptr_in_line, int line_index, Bool *error) {
    if(!is_str_empty(ptr_in_line)) {
        HANDLE_ERROR("Unidentified text after end of line", line_index);
            return;
    }
}

address_type validate_param(clist param, int * param_data, int line_index, ptable symbols_table, Bool *error) {
    char * param_str;
    if(get_char_from_list(param, 0) == '@') {
        unsigned short reg = get_char_from_list(param, 2) - '0';
        if (reg < 0 || 7 < reg || get_length(param) > 3 || get_char_from_list(param, 1) != 'r') {
            HANDLE_ERROR("unknown register", line_index);
            return IMM_REG_ADDR;
        }
        return IMM_REG_ADDR;
    }
     param_str = list_to_string(param);
    if(string_to_number(param_str, param_data)) {
        printf("Found Data: %d\n", *param_data);
        return ABS_ADDR;
    }
    if(is_param_label(param)) {
        return IMM_ADDR;
    }
    HANDLE_ERROR("unknown parameter type", line_index);
    free(param_str);
    return ABS_ADDR;
}

Bool is_param_label(clist param) {
    int i = 0;
    if(get_length(param) >= 32) {
        return False;
    }
    if(isalpha(get_char_from_list(param, i))) {
        for (i=1; i < get_length(param); i++) {
            if(!isalnum(get_char_from_list(param, i))) {
                return False;
            }
        }
        return True;
    }
    return False;
}
char * read_data_instruction(char * ptr_in_line, data_instruction * inst, int line_index, Bool *error) {
    ptr_in_line = skip_spaces(ptr_in_line);
    if(strncmp(ptr_in_line, ".string", 7) == 0) {
        *inst = STRING;
        ptr_in_line += 7;

    } else if(strncmp(ptr_in_line, ".data", 5) == 0) {
        *inst = DATA;
        ptr_in_line += 5;
    } else if(strncmp(ptr_in_line, ".extern", 7) == 0) {
        ptr_in_line += 7;
        *inst = EXTERN;
    } else if (strncmp(ptr_in_line, ".entry", 6) == 0) {
        ptr_in_line += 6;
        *inst = ENTRY;
    } else {
        HANDLE_ERROR("unkonwn instruction type", line_index);
        return ptr_in_line;
    }
    if(!isspace(*ptr_in_line)) {
        HANDLE_ERROR("unkonwn instruction type", line_index);
    }
    return ptr_in_line;
}

void read_data(char * ptr_in_line, int line_index, plist data_image, Bool *error) {
    int param_data;
    clist param = create_clist();
    char * param_str;
    Bool read_param = False;
    int param_counter = 0;
    do {
        clear_clist(param);
        param_data = 0;
        ptr_in_line = read_next_param(ptr_in_line, param, &read_param);
        ptr_in_line = skip_spaces(ptr_in_line);
        if(read_param) {
            param_str = list_to_string(param);
            printf("Param number %d: '%s'\n", param_counter, param_str);
            param_counter++;
            if(string_to_number(param_str, &param_data)) {
                i_line data_line = create_iline(get_plist_length(data_image));
                set_data_full(data_line, param_data);
                plist_append(data_image, data_line);
            } else {
                HANDLE_ERROR("Data is not valid integer", line_index);
            }
            free(param_str);
            
        } else {
            if(param_counter == 0){
                HANDLE_ERROR("No data after data instruction", line_index);
                free_clist(param);
                return;
            } else {
                if(*ptr_in_line == ',') {
                    HANDLE_ERROR("Extra comma after data", line_index);
                    free_clist(param);
                    return;
                }
            }    
        }
        if(*ptr_in_line == ',') {
            ptr_in_line++;
        } else if(*ptr_in_line != '\0'){    
            printf("c: '%c'\n", *ptr_in_line);
            HANDLE_ERROR("Missing comma between params", line_index);
            free_clist(param);
            return;
        }
    } while (*ptr_in_line != '\0');
    free_clist(param);
    
}

void read_string(char * ptr_in_line, int line_index, clist str, Bool *error) {
    ptr_in_line = skip_spaces(ptr_in_line);
    if(*ptr_in_line != '"') {
        HANDLE_ERROR("Invalid string, missing '\"' before string", line_index);
        free_clist(str);
        return;
    }
    ptr_in_line++;
    while (*ptr_in_line != '\0' && *ptr_in_line != '"') {
        append_char(str, *ptr_in_line);
        ptr_in_line++;
    }
    if(*ptr_in_line == '"') {
        ptr_in_line++;
    } else {
        HANDLE_ERROR("Invalid string, missing '\"' after string", line_index);
        return;
    }
    if(!is_str_empty(ptr_in_line)){
        HANDLE_ERROR("Unideintified text after .string instruction", line_index);
        return;
    }
}

void read_externals(char * ptr_in_line, ptable symbols_table, int line_index, plist externals, Bool *error) {
    clist param = create_clist();
    char * param_str;
    Bool read_param = False;
    int param_counter = 0;
    do {
        clear_clist(param);
        ptr_in_line = read_next_param(ptr_in_line, param, &read_param);
        ptr_in_line = skip_spaces(ptr_in_line);
        if(read_param) {
            param_counter++;
            param_str = list_to_string(param);
            printf("Found external %d: '%s'\n", param_counter, param_str);
            if(is_param_label(param)) {
                if(ptable_get(symbols_table, param_str) == NULL) {
                    symbol sym = create_symbol();
                    symbol_set_offset(sym, 0);
                    symbol_set_is_data(sym, False);
                    symbol_set_encoding(sym, E);
                    ptable_insert(symbols_table, param_str, sym);
                    plist_append(externals, param_str);
                } else {
                    HANDLE_ERROR("already defined symbol", line_index);
                }
            } else {
                HANDLE_ERROR("Not a valid symbol name", line_index);
            }
            
        } else {
            if(param_counter == 0){
                HANDLE_ERROR("No symbols after .extern instruction", line_index);
                free_clist(param);
                return;
            } else {
                if(*ptr_in_line == ',') {
                    HANDLE_ERROR("Extra comma after symbols", line_index);
                    free_clist(param);
                    return;
                }
            }    
        }
        if(*ptr_in_line == ',') {
            ptr_in_line++;
        } else if(*ptr_in_line != '\0'){ 
            HANDLE_ERROR("Missing comma between params", line_index);
            free_clist(param);
            return;
        }
    } while (*ptr_in_line != '\0');
    free_clist(param);

}

void read_entries(char * ptr_in_line, plist entries, int line_index, Bool *error) {
    clist param = create_clist();
    char * param_str;
    Bool read_param = False;
    int param_counter = 0;
    do {
        clear_clist(param);
        ptr_in_line = read_next_param(ptr_in_line, param, &read_param);
        ptr_in_line = skip_spaces(ptr_in_line);
        if(read_param) {
            param_counter++;
            param_str = list_to_string(param);
            printf("Found entry %d: '%s'\n", param_counter, param_str);
            if(is_param_label(param)) {
                plist_append(entries, param_str);
            } else {
                HANDLE_ERROR("Not a valid symbol name", line_index); 
            }
            
        } else {
            if(param_counter == 0){
                HANDLE_ERROR("No symbols after .extern instruction", line_index);
                free_clist(param);
                return;
            } else {
                if(*ptr_in_line == ',') {
                    HANDLE_ERROR("Extra comma after symbols", line_index);
                    free_clist(param);
                    return;
                }
            }    
        }
        if(*ptr_in_line == ',') {
            ptr_in_line++;
        } else if(*ptr_in_line != '\0'){ 
            HANDLE_ERROR("Missing comma between params", line_index);
            free_clist(param);
            return;
        }
    } while (*ptr_in_line != '\0');
    free_clist(param);

}