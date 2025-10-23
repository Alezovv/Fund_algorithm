#include "../include/Utils.h"

ValidCode ValidPaths(int argc, char *argv[])
{
    if (argc != 3)
    {
        print_usage();
        return VALID_WRONG_ARGUMETS;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
        return VALID_WRONG_PATH;

    fclose(file);

    file = fopen(argv[2], "r");
    if (file == NULL)
    {
        file = fopen(argv[2], "w");
        if (file == NULL)
            return VALID_WRONG_PATH;
    }
    fclose(file);
    return VALID_SUCCESS;
}

ValidCode ValidID(unsigned int *id)
{
    if (!scanf("%u", id))
        return VALID_ID_ERROR;
    return VALID_SUCCESS;
}

ValidCode ValidSurname(char *surname)
{
    char buffer[128];
    if (scanf("%127s", buffer) != 1)
        return VALID_SURNAME_ERROR;

    for (const char *ptr = buffer; *ptr != '\0'; ptr++)
    {
        if (!((*ptr >= 'A' && *ptr <= 'Z') || (*ptr >= 'a' && *ptr <= 'z')))
            return VALID_SURNAME_ERROR;
    }

    strcpy(surname, buffer);
    return VALID_SUCCESS;
}

ValidCode ValidGroup(char *group)
{
    if (group == NULL)
        return VALID_GROUP_ERROR;

    if (scanf("%127s", group) != 1)
        return VALID_GROUP_ERROR;

    return VALID_SUCCESS;
}

ValidCode ValidOptions(int *key)
{
    if (scanf("%d", key) != 1)
        return VALID_WRONG_OPTIONS;

    if (*key >= 0 && *key <= 3)
        return VALID_SUCCESS;

    return VALID_WRONG_OPTIONS;
}
