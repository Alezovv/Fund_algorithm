#ifndef VALIDATION_H
#define VALIDATION_H

typedef enum
{
    VALIDATION_SUCCESS = 0,
    VALIDATION_INVALID_EPSILON,
    VALIDATION_INVALID_NUMBER,
    VALIDATION_ZERO_DIVISION,
    VALIDATION_NON_POSITIVE
} ValidationStatus;

ValidationStatus validate_epsilon(double epsilon);
ValidationStatus validate_number(const char *str, int *result);
ValidationStatus validate_positive(double number);

#endif