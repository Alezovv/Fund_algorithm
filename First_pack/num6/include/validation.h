#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdlib.h>
#include <stdio.h>

typedef enum
{
    VALIDATION_SUCCESS = 0,
    VALIDATION_INVALID_EPSILON,
    VALIDATION_INVALID_ARGUMENTS,
    VALIDATION_EPSILON_OUT_OF_RANGE,
    VALIDATION_INVALID_LETTER
} ValidationStatus;

ValidationStatus validate_arguments(int argc, char *argv[]);

ValidationStatus validate_epsilon(const char *e);

ValidationStatus validate_letter(const char *l);

#endif // VALIDATION_H