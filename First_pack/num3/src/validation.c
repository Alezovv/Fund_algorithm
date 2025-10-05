#include "../include/validation.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

ValidationStatus validate_epsilon(double epsilon)
{
    if (epsilon <= 0 || epsilon >= 1)
    {
        return VALIDATION_INVALID_EPSILON;
    }
    return VALIDATION_SUCCESS;
}

ValidationStatus validate_number(const char *str, int *result)
{
    if (str == NULL || str[0] == '\0')
    {
        return VALIDATION_INVALID_NUMBER;
    }

    char *endptr;
    long num = strtol(str, &endptr, 10);

    if (*endptr != '\0')
    {
        return VALIDATION_INVALID_NUMBER;
    }

    *result = (int)num;
    return VALIDATION_SUCCESS;
}

ValidationStatus validate_positive(double number)
{
    if (number <= 0)
    {
        return VALIDATION_NON_POSITIVE;
    }
    return VALIDATION_SUCCESS;
}