#ifndef VALIDATION_H
#define VALIDATION_H

#define MAX_PRECISION 20

typedef enum
{
    VALIDATION_SUCCESS = 0,
    VALIDATION_INVALID_PRECISION,
    VALIDATION_INVALID_METHOD
} ValidationStatus;

ValidationStatus validate_precision(double precision);
ValidationStatus validate_method(int method);

#endif // VALIDATION_H