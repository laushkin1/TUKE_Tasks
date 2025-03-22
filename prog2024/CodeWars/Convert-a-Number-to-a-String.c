#include <stdio.h>

//  return a dynamically allocated C-string
//  this output will be freed by the tester

char *number_to_string(int number) {

    //  <----  hajime!
    char *str;
    asprintf(&str, "%d", number);
    return str;
}
