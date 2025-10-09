#include "../include/validation.h"

ValidationStatus validate_arguments(int argc, char *argv[])
{
    if (argc != 3)
    {
        return VALIDATION_INVALID_ARGC;
    }

    ValidationStatus flag_status = validate_flag(argv[1]);
    if (flag_status != VALIDATION_SUCCESS)
    {
        return flag_status;
    }

    long long number;
    ValidationStatus number_status = validate_number(argv[2], &number);
    if (number_status != VALIDATION_SUCCESS)
    {
        return number_status;
    }

    return VALIDATION_SUCCESS;
}

ValidationStatus validate_number(const char *str, long long *result)
{
    if (str == NULL || str[0] == '\0')
    {
        return VALIDATION_EMPTY_STRING;
    }

    if (str[0] == '-')
    {
        return VALIDATION_NUMBER_TOO_SMALL;
    }

    long long value = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)str[i]))
        {
            return VALIDATION_INVALID_SYMBOL;
        }

        if (value > (LLONG_MAX - (str[i] - '0')) / 10)
        {
            return VALIDATION_NUMBER_TOO_LARGE;
        }

        value = value * 10 + (str[i] - '0');
    }

    *result = value;
    return VALIDATION_SUCCESS;
}

ValidationStatus validate_flag(const char *flag)
{
    if (flag == NULL || flag[0] == '\0')
    {
        return VALIDATION_EMPTY_STRING;
    }

    if (flag[0] != '-' && flag[0] != '/')
    {
        return VALIDATION_INVALID_FLAG;
    }

    const char *valid_flags[] = {"-h", "-p", "-s", "-e", "-a", "-f",
                                 "/h", "/p", "/s", "/e", "/a", "/f", NULL};

    for (int i = 0; valid_flags[i] != NULL; i++)
    {
        if (strcmp(flag, valid_flags[i]) == 0)
        {
            return VALIDATION_SUCCESS;
        }
    }

    return VALIDATION_INVALID_FLAG;
}