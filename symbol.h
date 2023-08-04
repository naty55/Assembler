#ifndef __SYMBOL_H
#define __SYMBOL_H
#include "constants.h"
#include "util.h"
typedef struct Symbol *symbol; 

symbol create_symbol();
unsigned int symbol_get_address(symbol sym);
encoding symbol_get_encoding(symbol sym);
Bool symbol_is_data(symbol sym);
Bool symbol_is_set(symbol sym);
void symbol_set_address(symbol sym, unsigned int address);
void symbol_set_encoding(symbol sym, encoding encode);
void symbol_set_is_data(symbol sym, Bool is_data);
void symbol_set_is_set(symbol sym, Bool is_set);

#endif