#include "../include/function.h"
#include "../include/validation.h"

void print_usage()
{
    printf("Usage: <program> <function_number> <epsilon>\n");
    printf("Example: main a 0.001\n");
}

void handle_validation_error(ValidationStatus status)
{
    switch (status)
    {
    case VALIDATION_INVALID_ARGUMENTS:
        printf("Error: Invalid number of arguments\n");
        break;
    case VALIDATION_INVALID_EPSILON:
        printf("Error: epsilon must be a positive number\n");
        break;
    case VALIDATION_EPSILON_OUT_OF_RANGE:
        printf("Error: epsilon must be in the range (0, 1)\n");
        break;
    case VALIDATION_INVALID_LETTER:
        printf("Error: the letter must be a / b / c / d\n");
        break;
    default:
        printf("Error: undefined error\n");
    }
}

int main(int argc, char *argv[])
{
    ValidationStatus status = validate_arguments(argc, argv);
    if (status != VALIDATION_SUCCESS)
    {
        handle_validation_error(status);
        print_usage();
        return 1;
    }

    char letter = *argv[1];
    double eps = strtod(argv[2], NULL);
    double result = 0;

    double (*func[4])(double) = {
        func_a,
        func_b,
        func_c,
        func_d};

    int func_index = letter - 'a';
    if (func_index >= 0 && func_index < 4)
    {
        result = integral(func[func_index], eps);
    }
    else
    {
        printf("Error: undefined function '%c'\n", letter);
    }

    printf("Solution for the integral %c: %.10f\n", letter, result);

    return 0;
}