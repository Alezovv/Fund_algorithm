#ifndef VALIDATION_H
#define VALIDATION_H

#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef enum
{
    VALIDATION_SUCCESS,
    VALIDATION_INVALID_ARGC,
    VALIDATION_INVALID_FLAG,
    VALIDATION_INVALID_NUMBER,
    VALIDATION_NUMBER_TOO_LARGE,
    VALIDATION_NUMBER_TOO_SMALL,
    VALIDATION_INVALID_SYMBOL,
    VALIDATION_EMPTY_STRING
} ValidationStatus;

ValidationStatus validate_arguments(int argc, char *argv[]);
ValidationStatus validate_number(const char *str, long long *result);
ValidationStatus validate_flag(const char *flag);

#endif // VALIDATION_H
