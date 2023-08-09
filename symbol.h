#ifndef __SYMBOL_H
#define __SYMBOL_H
#include "constants.h"
#include "util.h"
/**
 * Symbol represent a label in the assembly file, it has metdata 
 * encoding type, is_data symbol (if the lable represent data .string or .data)
 * is_set if the address is set correctly - the second phase should set it for data labels.
*/
typedef struct Symbol *symbol; 
/**
 * Create symbol - set is_set to False.
*/
symbol create_symbol();
/**
 * get address in the binary code of the symbol (if external return 0)
*/
unsigned int symbol_get_address(symbol sym);
/**
 * get encoding of symbol as definesd in the course guide
*/
encoding symbol_get_encoding(symbol sym);
/**
 * is symbol data 
*/
Bool symbol_is_data(symbol sym);
/**
 * is address of symbol set
*/
Bool symbol_is_set(symbol sym);
/**
 * set symbol address
*/
void symbol_set_address(symbol sym, unsigned int address);
/**
 * set symbol encoding
*/
void symbol_set_encoding(symbol sym, encoding encode);
/**
 * set is symbol data
*/
void symbol_set_is_data(symbol sym, Bool is_data);
/**
 * set is symbol set.
*/
void symbol_set_is_set(symbol sym, Bool is_set);

#endif