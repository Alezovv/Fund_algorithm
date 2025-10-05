#include "../include/validation.h"

ValidationStatus validate_arguments(int argc, char *argv[])
{
    if (argc != 3)
    {
        return VALIDATION_INVALID_ARGUMENTS;
    }

    ValidationStatus status = validate_epsilon(argv[2]);
    if (status != VALIDATION_SUCCESS)
    {
        return status;
    }

    status = validate_letter(argv[1]);
    if (status != VALIDATION_SUCCESS)
    {
        return status;
    }

    return VALIDATION_SUCCESS;
}

ValidationStatus validate_epsilon(const char *e)
{
    char *ptr;
    double epsilon = strtod(e, &ptr);

    if (*ptr != '\0' || epsilon <= 0.0)
    {
        return VALIDATION_INVALID_EPSILON;
    }

    if (epsilon >= 1.0)
    {
        return VALIDATION_INVALID_EPSILON;
    }

    return VALIDATION_SUCCESS;
}

ValidationStatus validate_letter(const char *l)
{
    if (l[0] == '\0' || l[1] != '\0')
    {
        return VALIDATION_INVALID_LETTER;
    }

    if (l[0] == 'a' || l[0] == 'b' || l[0] == 'c' || l[0] == 'd')
    {
        return VALIDATION_SUCCESS;
    }

    return VALIDATION_INVALID_LETTER;
}