#include "../include/Student.h"

typedef enum ValidCode
{
    VALID_SUCCESS = 0,
    VALID_ID_ERROR,
    VALID_WRONG_OPTIONS,
    VALID_WRONG_PATH,
    VALID_WRONG_ARGUMETS,
    VALID_SURNAME_ERROR,
    VALID_GROUP_ERROR
} ValidCode;

ValidCode ValidID(unsigned int *id);

ValidCode ValidOptions(int *key);

ValidCode ValidPaths(int argc, char *argv[]);

ValidCode ValidSurname(char *surname);

ValidCode ValidGroup(char *group);