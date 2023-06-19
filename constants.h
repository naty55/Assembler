#ifndef __CONST_H
#define __CONST_H
#define MAX_LINE_SIZE 100

#define MACRO "mcro"
#define ENDMACRO "endmcro"

typedef enum {
    A = 0,
    E = 1,
    R = 2
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

#endif