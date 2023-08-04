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
        HANDLE_ERROR("unkonwn operation", line_index, error);
    }
    ptr_in_line += 3;
    if(!isspace(*ptr_in_line) && *ptr_in_line != '\n' && *ptr_in_line != '\0') {
        HANDLE_ERROR("unknown operation", line_index, error);
    }
    return ptr_in_line;
}

char * read_label(char *ptr_in_line ,int line_index, ptable symbols_table, symbol* sym, unsigned int image_index, Bool *error) {
    char * label;
    ptr_in_line = skip_spaces(ptr_in_line);
    label = ptr_in_line;
    if(*ptr_in_line == '.') {
        return ptr_in_line;
    }
    if((ptr_in_line = strchr(ptr_in_line, ':')) != NULL) {
        if(ptr_in_line - label >= 31) {
            HANDLE_ERROR("too long label name", line_index, error);
            return ptr_in_line;
        } 
        if (ptr_in_line - label == 0) {
            HANDLE_ERROR("label name must be at least of size 1", line_index, error);
            return ptr_in_line;
        }
        *ptr_in_line = 0;
        ptr_in_line = skip_spaces(ptr_in_line + 1);
        if(is_keyword(label)) {
            HANDLE_ERROR("label name is saved keyword", line_index, error);
            return ptr_in_line;
        }
        
        *sym = create_symbol();
        symbol_set_encoding(*sym, R);
        symbol_set_address(*sym, IMAGE_OFFSET_SIZE + image_index);
        symbol_set_is_data(*sym, False);
        symbol_set_is_set(*sym, True);
        ptable_insert(symbols_table, label ,*sym);
        DEBUG_1PARAM_STR("Found Label :", label);
        DEBUG_1PARAM_INT("Label location:", symbol_get_address(ptable_get(symbols_table, label)));
        
    } else {
        ptr_in_line = label;
    }
    return ptr_in_line;
}

char * get_next_param(char *ptr_in_line, clist param, Bool *read_param, int line_index, Bool *error) {
    clist_clear(param);
    *read_param = False;
    ptr_in_line = skip_spaces(ptr_in_line);
    if(*ptr_in_line != ',') {
        HANDLE_ERROR("missing comma between params", line_index, error);
        return ptr_in_line;
    }
    ptr_in_line++;
    return read_next_param(ptr_in_line, param, read_param);
}

char * read_next_param(char * ptr_in_line, clist param, Bool *read_param) {
    ptr_in_line = skip_spaces(ptr_in_line);
    while (*ptr_in_line != '\0' && !isspace(*ptr_in_line) && *ptr_in_line != ',') {
        clist_append_char(param, *ptr_in_line++);
        *read_param = True;
    }
    return ptr_in_line;
}

void check_for_extra_text(char *ptr_in_line, int line_index, Bool *error) {
    if(!is_str_empty(ptr_in_line)) {
        HANDLE_ERROR("Unidentified text after end of line", line_index, error);
    }
}

address_type validate_param(clist param, int * param_data, int line_index, ptable symbols_table, Bool *error) {
    char * param_str;
    if(clist_get_length(param) == 0) {
        HANDLE_ERROR("missing parameter", line_index, error);
        return ABS_ADDR;
    }
    if(clist_get(param, 0) == '@') {
        unsigned short reg = clist_get(param, 2) - '0';
        if (reg < 0 || 7 < reg || clist_get_length(param) > 3 || clist_get(param, 1) != 'r') {
            HANDLE_ERROR("unknown register", line_index, error);
            return IMM_REG_ADDR;
        }
        return IMM_REG_ADDR;
    }
    param_str = clist_to_string(param);
    if(string_to_number(param_str, param_data)) {
        DEBUG_1PARAM_INT("Found Data:", *param_data);
        return ABS_ADDR;
    }
    if(is_param_label(param)) {
        return IMM_ADDR;
    }
    HANDLE_ERROR("unknown parameter type", line_index, error);
    free(param_str);
    return ABS_ADDR;
}

Bool is_param_label(clist param) {
    int i = 0;
    if(clist_get_length(param) == 0 || clist_get_length(param) >= 32) {
        return False;
    }
    if(isalpha(clist_get(param, i))) {
        for (i=1; i < clist_get_length(param); i++) {
            if(!isalnum(clist_get(param, i))) {
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
        HANDLE_ERROR("unkonwn instruction type", line_index, error);
        return ptr_in_line;
    }
    if(!isspace(*ptr_in_line)) {
        HANDLE_ERROR("unkonwn instruction type", line_index, error);
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
        clist_clear(param);
        param_data = 0;
        ptr_in_line = read_next_param(ptr_in_line, param, &read_param);
        ptr_in_line = skip_spaces(ptr_in_line);
        if(read_param) {
            param_str = clist_to_string(param);
            DEBUG_2PARAM("Found param:", param_str, param_counter);
            param_counter++;
            if(string_to_number(param_str, &param_data)) {
                i_line data_line = create_iline(plist_get_length(data_image));

                if(param_data < -2048 || 2047 < param_data) {
                    param_data = 0;
                    WARN("data overflow, will set data to 0", line_index);
                }
                i_line_set_data_full(data_line, param_data);
                plist_append(data_image, data_line);
            } else {
                HANDLE_ERROR("Data is not valid integer", line_index, error);
            }
            free(param_str);
            
        } else {
            if(param_counter == 0){
                HANDLE_ERROR("No data after data instruction", line_index, error);
                clist_free(param);
                return;
            } else {
                if(*ptr_in_line == ',') {
                    HANDLE_ERROR("Extra comma after data", line_index, error);
                    clist_free(param);
                    return;
                }
            }    
        }
        READ_COMMA();
    } while (*ptr_in_line != '\0');
    clist_free(param);
    
}

void read_string(char * ptr_in_line, int line_index, clist str, Bool *error) {
    ptr_in_line = skip_spaces(ptr_in_line);
    if(*ptr_in_line != '"') {
        HANDLE_ERROR("Invalid string, missing '\"' before string", line_index, error);
        clist_free(str);
        return;
    }
    ptr_in_line++;
    while (*ptr_in_line != '\0' && *ptr_in_line != '"') {
        clist_append_char(str, *ptr_in_line);
        ptr_in_line++;
    }
    if(*ptr_in_line == '"') {
        ptr_in_line++;
    } else {
        HANDLE_ERROR("Invalid string, missing '\"' after string", line_index, error);
        return;
    }
    if(!is_str_empty(ptr_in_line)){
        HANDLE_ERROR("Unideintified text after .string instruction", line_index, error);
        return;
    }
}

void read_externals(char * ptr_in_line, ptable symbols_table, int line_index, plist externals, Bool *error) {
    clist param = create_clist();
    char * param_str;
    Bool read_param = False;
    int param_counter = 0;
    do {
        clist_clear(param);
        ptr_in_line = read_next_param(ptr_in_line, param, &read_param);
        ptr_in_line = skip_spaces(ptr_in_line);
        if(read_param) {
            symbol sym;
            param_counter++;
            param_str = clist_to_string(param);
            DEBUG_2PARAM("Found external ", param_str, param_counter);
            if(!is_param_label(param)) {
                HANDLE_ERROR("Not a valid symbol name", line_index, error);
                free(param_str);
                READ_COMMA();
                continue;
            }
            if(is_keyword(param_str)) {
                HANDLE_ERROR("label name is saved keyword", line_index, error);
                free(param_str);
                READ_COMMA();
                continue;
            }
            sym = ptable_get(symbols_table, param_str);
            if(sym == NULL) {
                symbol sym = create_symbol();
                symbol_set_address(sym, 0);
                symbol_set_is_data(sym, False);
                symbol_set_encoding(sym, E);
                symbol_set_is_set(sym, True);
                ptable_insert(symbols_table, param_str, sym);
                plist_append(externals, param_str);
            } else {
                if(symbol_get_encoding(sym) == E) {
                    WARN_1PARAM("external is already defined", line_index, param_str);
                } else {
                    HANDLE_ERROR("already defined symbol", line_index, error);
                }
            }
            
        } else {
            if(param_counter == 0){
                HANDLE_ERROR("No symbols after .extern instruction", line_index, error);
                clist_free(param);
                return;
            } else {
                if(*ptr_in_line == ',') {
                    HANDLE_ERROR("Extra comma after symbols", line_index, error);
                    clist_free(param);
                    return;
                }
            }    
        }
        READ_COMMA();
    } while (*ptr_in_line != '\0');
    clist_free(param);

}

void read_entries(char * ptr_in_line, ptable entries, int line_index, Bool *error) {
    clist param = create_clist();
    char * param_str;
    Bool read_param = False;
    Bool is_declared_as_entry = False;
    int param_counter = 0;
    do {
        clist_clear(param);
        ptr_in_line = read_next_param(ptr_in_line, param, &read_param);
        ptr_in_line = skip_spaces(ptr_in_line);
        if(!read_param) {
            if(param_counter == 0){
                HANDLE_ERROR("No symbols after .extern instruction", line_index, error);
                clist_free(param);
                return;
            } else {
                if(*ptr_in_line == ',') {
                    HANDLE_ERROR("Extra comma after symbols", line_index, error);
                    clist_free(param);
                    return;
                }
            }    
        }
        param_counter++;
        param_str = clist_to_string(param);
        DEBUG_2PARAM("Found entry", param_str, param_counter);
        if(!is_param_label(param)) {
            HANDLE_ERROR("Not a valid symbol name", line_index, error);
            free(param_str);
            READ_COMMA();
            continue;
        }
        if(is_keyword(param_str)) {
            HANDLE_ERROR("label name is saved keyword", line_index, error);
            free(param_str);
            READ_COMMA();
            continue;
        }
        is_declared_as_entry = (Bool)(ptable_get(entries, param_str) != NULL);
        if(!is_declared_as_entry) {
            ptable_insert(entries, param_str, create_bool(True));
        } else {
            WARN_1PARAM("entry is already declared", line_index, param_str);
        }    
        free(param_str);
        
        READ_COMMA();
    } while (*ptr_in_line != '\0');
    clist_free(param);
}