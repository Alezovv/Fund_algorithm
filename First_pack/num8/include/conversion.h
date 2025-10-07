#ifndef CONVERSION_H
#define CONVERSION_H

#include <stddef.h>

typedef enum
{
    CONVERSION_SUCCESS = 0,
    CONVERSION_INVALID_BASE,
    CONVERSION_INVALID_INPUT,
    CONVERSION_OVERFLOW,
    CONVERSION_BUFFER_TOO_SMALL,
    CONVERSION_NULL_POINTER
} ConversionStatus;

ConversionStatus str_to_ll(const char *str, int base, long long *result);
ConversionStatus ll_to_str(long long num, int base, char *buffer, size_t buffer_size, char **result_str);

#endif