#include "symbol.h"
#include "util.h"
#include "constants.h"
#include <stdlib.h>

struct Symbol {
    unsigned int address;
    encoding encode;
    Bool is_data;
    Bool is_set;
    unsigned long declared_at_assembly_line; /* Assembly line where the symbol is declared*/
};

symbol create_symbol(unsigned declared_at_assembly_line) {
    symbol sym = malloc_safe(sizeof(struct Symbol));
    sym->is_set = False;
    sym->declared_at_assembly_line = declared_at_assembly_line;
    return sym;
}

unsigned int symbol_get_address(symbol sym) {
    return sym->address;
}

encoding symbol_get_encoding(symbol sym) {
    return sym->encode;
}

unsigned int symbol_get_declared_at_line(symbol sym) {
    return sym->declared_at_assembly_line;
}

Bool symbol_is_data(symbol sym) {
    return sym->is_data;
}

Bool symbol_is_set(symbol sym) {
    return sym->is_set;
}

void symbol_set_address(symbol sym, unsigned int address) {
    sym->address = address;
}

void symbol_set_encoding(symbol sym, encoding encode) {
    sym->encode = encode;
}

void symbol_set_is_data(symbol sym, Bool is_data) {
    sym->is_data = is_data;
}

void symbol_set_is_set(symbol sym, Bool is_set) {
    sym->is_set = is_set;
}