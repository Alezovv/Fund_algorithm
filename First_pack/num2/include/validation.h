#ifndef VALIDATION_H
#define VALIDATION_H

#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef enum
{
    VALIDATION_SUCCESS,
    VALIDATION_NUMBER_TOO_SMALL,
    VALIDATION_NUMBER_ZERO
} ValidationStatus;

ValidationStatus validate_number(int number);

#endif // VALIDATION_H
