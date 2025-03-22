#include <ctype.h>
#include "str_utils.h"
#include <stdbool.h>

/** Remove all spaces from a string. */
void str_remove_spaces(char *str) {
    const char *character = str;
    do {
        while (isspace(*character)) {
            ++character;
        }
    } while ((*str++ = *character++));
}

bool is_valid_integer(const char *str) {
    if (!str || *str == '\0') {
        return false;
    }
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}
