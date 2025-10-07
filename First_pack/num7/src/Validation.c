#include "../include/Validation.h"
#include <stdio.h>

ValidationStatus Validate_Argument(int argc, char *argv[])
{
    if (argc != 3)
    {
        return VALIDATION_INVALID_ARGUMENTS;
    }

    ValidationStatus status = VALIDATION_SUCCESS;
    for (int i = 1; i < 3; i++)
    {
        status = Validate_File(argv[i]);
        if (status != VALIDATION_SUCCESS)
        {
            printf("Path: %s\n", argv[i]);
            return status;
        }
    }

    return VALIDATION_SUCCESS;
}

ValidationStatus Validate_File(const char *path)
{
    if (path == NULL)
    {
        return VALIDATION_FILE_NOT_FOUND;
    }

    FILE *file = fopen(path, "r+");

    if (file == NULL)
    {
        return VALIDATION_FILE_NOT_FOUND;
    }

    fclose(file);
    return VALIDATION_SUCCESS;
}

ValidationStatus Validate_Number(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        return VALIDATION_SUCCESS;
    }
    return VALIDATION_WRONG_NUMBER;
}