#include "constants.h"

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