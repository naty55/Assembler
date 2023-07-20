#include "symbol.h"
#include "util.h"
#include "constants.h"
#include <stdlib.h>

struct Symbol {
    unsigned int offset;
    encoding encode;
    Bool is_data;
};

symbol create_symbol() {
    symbol sym = malloc(sizeof(struct Symbol));
    return sym;
}

unsigned int symbol_get_offset(symbol sym) {
    return sym->offset;
}

encoding symbol_get_encoding(symbol sym) {
    return sym->encode;
}

Bool symbol_is_data(symbol sym) {
    return sym->is_data;
}

void symbol_set_offset(symbol sym, unsigned int offset) {
    sym->offset = offset;
}

void symbol_set_encoding(symbol sym, encoding encode) {
    sym->encode = encode;
}

void symbol_set_is_data(symbol sym, Bool is_data) {
    sym->is_data = is_data;
}