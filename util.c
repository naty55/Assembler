#include <ctype.h>
#include "util.h"



char * skip_spaces(char * str) {
    while (isspace(*(str++)));
    return --str;
}
Bool is_str_empty(char * str) {
    return (Bool)(*skip_spaces(str) == '\0');
}