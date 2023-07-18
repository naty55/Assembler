#ifndef __SYMBOL_H
#define __SYMBOL_H
#include "constants.h"
typedef struct Symbol *symbol; 

symbol create_symbol();
int symbol_get_offset(symbol sym);
encoding symbol_get_encoding(symbol sym);
void symbol_set_offset(symbol sym, int offset);
void symbol_set_encoding(symbol sym, encoding encode);

#endif