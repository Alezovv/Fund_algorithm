#ifndef STATUSCODE_H
#define STATUSCODE_H

#include <stdio.h>

#define CHECK                     \
    if (status != STATUS_SUCCESS) \
        return status;

typedef enum
{
    STATUS_SUCCESS = 0,
    STATUS_STRING_EMPTY,
    STATUS_ERROR_OVERFLOW,
    STATUS_ERROR_MEMORY_ALLOCATE,
    STATUS_ERROR_NOT_CREATED_STACK,
    STATUS_ERROR_EMPTY_STACK,
    STATUS_ERROR_WRONG_ARGUMENT,
    STATUS_ERROR_NOT_ENOUGH_BRACKETS

} StatusCode;

void print_usage();

void handle_error(StatusCode status);

#endif // STATUSCODE_H