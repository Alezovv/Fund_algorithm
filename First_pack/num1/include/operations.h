#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef enum
{
    OPERATION_SUCCESS,
    OPERATION_INVALID_INPUT,
    OPERATION_OVERFLOW,
    OPERATION_NO_RESULTS,
    OPERATION_OUT_OF_RANGE
} OperationStatus;

// Флаг -h
OperationStatus find_multiples(long long x, int **results, size_t *count);

// Флаг -p
OperationStatus check_prime(long long x, int *is_prime, int *is_composite);

// Флаг -s
OperationStatus split_hex_digits(long long x, char **result, size_t *length);

// Флаг -e
OperationStatus print_power_table(long long x);

// Флаг -a
OperationStatus calculate_sum(long long x, unsigned long long *result);

// Флаг -f
OperationStatus calculate_factorial(long long x, unsigned long long *result);

#endif