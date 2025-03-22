#include <string.h>

char* remove_char(char* dst, const char* src)
{
    /* src is the input string */
    /* your solution should write the result into dst and return it */

    int len = strlen(src);

    for (int i = 0; i<len-1; i++){
        if(i!=0) dst[i-1] = src[i];
    }
    dst[len-2] = '\0';
    return dst;
}

