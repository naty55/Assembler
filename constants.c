#include "constants.h"
#include "util.h"

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

