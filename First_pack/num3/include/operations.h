#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdbool.h>

typedef enum
{
    SUCCESS = 0,
    ERROR_INVALID_ARGUMENTS,
    ERROR_INVALID_EPSILON,
    ERROR_INVALID_NUMBER,
    ERROR_NOT_MULTIPLE,
    ERROR_NOT_RIGHT_TRIANGLE
} OperationStatus;

OperationStatus solve_quadratic_permutations(double epsilon, double a, double b, double c);
OperationStatus check_multiple(int num1, int num2, bool *is_multiple);
OperationStatus check_right_triangle(double epsilon, double a, double b, double c, bool *is_right);

#endif