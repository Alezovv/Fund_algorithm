#include "../include/function.h"

static void from_rom(const char *str, int *result)
{
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *numerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
}

int overfscanf(FILE *stream, const char *format, ...)
{
    if (stream == NULL || format == NULL)
        return -1;
    va_list args;
    va_start(args, format);
    int count = 0;
}