#include "constants.h"
#include "util.h"
#include "string.h"
#include <stdio.h>

short get_params_to_read(operation op) {
    switch (op)
    {
    case MOV:
    case CMP:
    case ADD:
    case SUB:
    case LEA:
        return 2;
    case NOT:
    case CLR:
    case INC:
    case DEC:
    case JMP:
    case BNE:
    case RED:
    case PRN:
    case JSR:
        return 1;
    default:
        return 0;
    }
}

Bool validate_op_and_target_param(operation op, address_type param_type) {
    switch (op)
    {
        case MOV:
        case ADD:
        case SUB:
        case LEA:
        case NOT:
        case CLR:
        case INC:
        case DEC:
        case JMP:
        case BNE:
        case RED:
        case JSR:
            return (Bool)(param_type == IMM_ADDR || param_type == IMM_REG_ADDR);
        case CMP:
        case PRN:
            return True;
        default:
            return False;
    }   
}

Bool validate_op_and_source_param(operation op, address_type param_type) {
    switch (op)
    {
        case MOV:
        case ADD:
        case SUB:
        case CMP:
            return True;
        case LEA:
            return (Bool)(param_type == IMM_ADDR);
        case CLR:
        case INC:
        case DEC:
        case JMP:
        case BNE:
        case RED:
        case JSR:
        case PRN:
        default:
            return False;
    }   
}


Bool is_keyword(char * str) {
    return (Bool) (
        strcmp(str, "mov") == 0 ||
        strcmp(str, "cmp") == 0 ||
        strcmp(str, "add") == 0 ||
        strcmp(str, "sub") == 0 ||
        strcmp(str, "not") == 0 ||
        strcmp(str, "clr") == 0 ||
        strcmp(str, "lea") == 0 ||
        strcmp(str, "inc") == 0 ||
        strcmp(str, "dec") == 0 ||
        strcmp(str, "jmp") == 0 ||
        strcmp(str, "bne") == 0 ||
        strcmp(str, "red") == 0 ||
        strcmp(str, "prn") == 0 ||
        strcmp(str, "jsr") == 0 ||
        strcmp(str, "rts") == 0 ||
        strcmp(str, "stop") == 0 
        );
}
