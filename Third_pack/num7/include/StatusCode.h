#ifndef STATUSCODE_H
#define STATUSCODE_H

#include <ctype.h>
#include <string.h>

#define CHECK              \
    if (status != SUCCESS) \
        return status;

typedef enum
{
    SUCCESS = 0,
    WRONG_ARGUMENT,
    MEMORY_ALLOCATE,
    STACK_EMPTY,
    FILE_ERROR
} StatusCode;

StatusCode Validate_Expression(char *str, int *expr);

#endif // STATUSCODE_H