#include "../include/validation.h"
#include "../include/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(const char *program)
{
    printf("Usage: %s <constant> <precision> <method>\n", program);
    printf("Constants: e, pi, ln2, sqrt2, gamma\n");
    printf("Precision: number of decimal digits (1-%d)\n", MAX_PRECISION);
    printf("Methods: 0-limits, 1-sum series, 2-equation\n");
    printf("Example: %s e 15 2\n", program);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        print_usage(argv[0]);
        return 1;
    }

    const char *constant_name = argv[1];
    int precision = atoi(argv[2]);
    int method_num = atoi(argv[3]);

    ValidationStatus val_status = validate_precision(precision);
    if (val_status != VALIDATION_SUCCESS)
    {
        printf("Error: precision must be between 1 and %d\n", MAX_PRECISION);
        return 1;
    }

    val_status = validate_method(method_num);
    if (val_status != VALIDATION_SUCCESS)
    {
        printf("Error: method must be 0, 1 or 2\n");
        return 1;
    }

    Method method;
    switch (method_num)
    {
    case 0:
        method = METHOD_LIMITS;
        break;
    case 1:
        method = METHOD_SERIES;
        break;
    case 2:
        method = METHOD_EQUATION;
        break;
    default:
        printf("Error: invalid method\n");
        return 1;
    }

    double result;
    ConstStatus status;

    if (strcmp(constant_name, "e") == 0)
    {
        status = calculate_e(method, &result);
    }
    else if (strcmp(constant_name, "pi") == 0)
    {
        status = calculate_pi(method, &result);
    }
    else if (strcmp(constant_name, "ln2") == 0)
    {
        status = calculate_ln2(method, &result);
    }
    else if (strcmp(constant_name, "sqrt2") == 0)
    {
        status = calculate_sqrt2(method, &result);
    }
    else if (strcmp(constant_name, "gamma") == 0)
    {
        status = calculate_gamma(method, &result);
    }
    else
    {
        printf("Error: unknown constant '%s'\n", constant_name);
        print_usage(argv[0]);
        return 1;
    }

    if (status == CONST_SUCCESS)
    {
        printf("Результат: %.*f\n", precision, result);
    }
    else
    {
        printf("Error: calculation failed for %s using method %d\n",
               constant_name, method_num);
        return 1;
    }

    return 0;
}