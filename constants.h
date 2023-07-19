#ifndef __CONST_H
#define __CONST_H
#define MAX_LINE_SIZE 100

#define MACRO "mcro"
#define ENDMACRO "endmcro"

typedef enum {
    A = 0, /*Absolute*/
    E = 1, /*External*/
    R = 2  /*Relocatable*/
} encoding;

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

typedef enum {
    ABS_ADDR = 1,
    IMM_ADDR = 3,
    IMM_REG_ADDR = 5
} address_type;

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

typedef enum {
    STRING,
    DATA,
    EXTERN,
    ENTRY
} data_instruction;


short get_params_to_read(operation op);

#endif