#include "../include/validations.h"

ValidationStatus validate_arguments(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        return VALIDATION_INVALID_ARGC;
    }

    ValidationStatus status = validate_flag(argv[1]);
    if (status != VALIDATION_SUCCESS)
    {
        return status;
    }

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

    const char *valid_flags[] = {"-d", "-i", "-s", "-a",
                                 "/d", "/i", "/s", "/a",
                                 "-nd", "-ni", "-ns", "-na",
                                 "/nd", "/ni", "/ns", "/na", NULL};

    for (int i = 0; valid_flags[i] != NULL; i++)
    {
        if (strcmp(flag, valid_flags[i]) == 0)
        {
            return VALIDATION_SUCCESS;
        }
    }

    return VALIDATION_INVALID_FLAG;
}

ValidationStatus validate_file(const char *filename)
{
    if (filename == NULL)
        return VALIDATION_INVALID_FILE;

    if (strlen(filename) == 0)
        return VALIDATION_INVALID_FILE;

    if (strlen(filename) < 1)
        return VALIDATION_INVALID_FILE;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return VALIDATION_INVALID_FILE;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size == 0)
    {
        fclose(file);
        return VALIDATION_INVALID_FILE;
    }
    fseek(file, 0, SEEK_SET);

    fclose(file);
    return VALIDATION_SUCCESS;
}