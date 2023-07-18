#include "symbol.h"
#include "constants.h"
#include <stdlib.h>

struct Symbol {
    int offset;
    encoding encode;
};

symbol create_symbol() {
    symbol sym = malloc(sizeof(struct Symbol));
    return sym;
}

int symbol_get_offset(symbol sym) {
    return sym->offset;
}

encoding symbol_get_encoding(symbol sym) {
    return sym->encode;
}

void symbol_set_offset(symbol sym, int offset) {
    sym->offset = offset;
}

void symbol_set_encoding(symbol sym, encoding encode) {
    sym->encode = encode;
}