#include "../include/validation.h"

ValidationStatus validate_precision(double precision)
{
    if (precision <= 0)
    {
        return VALIDATION_INVALID_PRECISION;
    }
    if (precision > MAX_PRECISION)
    {
        return VALIDATION_INVALID_PRECISION;
    }
    return VALIDATION_SUCCESS;
}

ValidationStatus validate_method(int method)
{
    if (method < 0 || method > 2)
    {
        return VALIDATION_INVALID_METHOD;
    }
    return VALIDATION_SUCCESS;
}