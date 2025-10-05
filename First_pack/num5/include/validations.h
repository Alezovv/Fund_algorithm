#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include <stdio.h>
#include <string.h>

typedef enum
{
    VALIDATION_SUCCESS = 0,
    VALIDATION_INVALID_ARGC,
    VALIDATION_INVALID_FLAG,
    VALIDATION_EMPTY_STRING,
    VALIDATION_INVALID_FILE
} ValidationStatus;

ValidationStatus validate_arguments(int argc, char *argv[]);

ValidationStatus validate_flag(const char *flag);

ValidationStatus validate_file(const char *filename);

#endif // VALIDATIONS_H