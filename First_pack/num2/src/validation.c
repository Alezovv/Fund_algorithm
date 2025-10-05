#include "../include/validation.h"

ValidationStatus validate_number(int number)
{
    if (number < 0)
    {
        return VALIDATION_NUMBER_TOO_SMALL;
    }
    else if (number == 0)
    {
        return VALIDATION_NUMBER_ZERO;
    }

    return VALIDATION_SUCCESS;
}
