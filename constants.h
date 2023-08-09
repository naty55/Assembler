#ifndef __CONST_H
#define __CONST_H
#include "util.h"

#define MAX_LINE_SIZE 81 

#define MACRO "mcro"
#define ENDMACRO "endmcro"
#define IMAGE_OFFSET_SIZE 100
/**
 * Encoding types
*/
typedef enum {
    Absolute = 0, /*Absolute*/
    External = 1, /*External*/
    Relocatable = 2  /*Relocatable*/
} encoding;
/**
 * Opcodes 
*/
typedef enum {
    MOV = 0,
    CMP = 1,
    ADD = 2,
    SUB = 3,
    NOT = 4,
    CLR = 5,
    LEA = 6,
    INC = 7,
    DEC = 8,
    JMP = 9,
    BNE = 10,
    RED = 11,
    PRN = 12,
    JSR = 13,
    RTS = 14,
    STP = 15
} operation;
/**
 * Addressing types 
*/
typedef enum {
    ABS_ADDR = 1,
    IMM_ADDR = 3,
    IMM_REG_ADDR = 5
} address_type;
/**
 * Registers 
*/
typedef enum {
    R0 = 0,
    R1 = 1,
    R2 = 2,
    R3 = 3,
    R4 = 4,
    R5 = 5,
    R6 = 6,
    R7 = 7
} register_name;
/**
 * Data instructions types
*/
typedef enum {
    STRING,
    DATA,
    EXTERN,
    ENTRY
} data_instruction;


short get_params_to_read(operation op);

/**
 * Validate param type matches the opernd code as target param
*/
Bool validate_op_and_target_param(operation op, address_type param_type);
/**
 * Validate param type matches the opernd code as sourde param
*/
Bool validate_op_and_source_param(operation op, address_type param_type);
/**
 * Return True if string a saved keyword (operand code)
*/
Bool is_keyword(char * str);
#endif