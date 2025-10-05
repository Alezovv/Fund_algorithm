#include "../include/validation.h"
#include "../include/operations.h"

void print_usage(void)
{
    printf("Usage: program <flag> <number>\n");
    printf("Flags:\n");
    printf("  -h  show natural numbers up to 100 that are multiples of x\n");
    printf("  -p  check if x is prime or composite\n");
    printf("  -s  split x into hexadecimal digits\n");
    printf("  -e  print power table (x must be <= 10)\n");
    printf("  -a  calculate sum of natural numbers from 1 to x\n");
    printf("  -f  calculate factorial of x\n");
}

void handle_validation_error(ValidationStatus status)
{
    switch (status)
    {
    case VALIDATION_INVALID_ARGC:
        printf("Error: Invalid number of arguments\n");
        break;
    case VALIDATION_INVALID_FLAG:
        printf("Error: Invalid flag\n");
        break;
    case VALIDATION_INVALID_NUMBER:
        printf("Error: Invalid number format\n");
        break;
    case VALIDATION_NUMBER_TOO_LARGE:
        printf("Error: Number is too large\n");
        break;
    case VALIDATION_NUMBER_TOO_SMALL:
        printf("Error: Number must be positive\n");
        break;
    case VALIDATION_INVALID_SYMBOL:
        printf("Error: Number contains invalid symbols\n");
        break;
    case VALIDATION_EMPTY_STRING:
        printf("Error: Empty string provided\n");
        break;
    default:
        printf("Error: Unknown validation error\n");
        break;
    }
}

void handle_operation_error(OperationStatus status)
{
    switch (status)
    {
    case OPERATION_INVALID_INPUT:
        printf("Error: Invalid input parameters\n");
        break;
    case OPERATION_OVERFLOW:
        printf("Error: Arithmetic overflow occurred\n");
        break;
    case OPERATION_NO_RESULTS:
        printf("No results found\n");
        break;
    case OPERATION_OUT_OF_RANGE:
        printf("Error: Number out of valid range\n");
        break;
    default:
        printf("Error: Unknown operation error\n");
        break;
    }
}

int main(int argc, char *argv[])
{
    // Валидация аргументов
    ValidationStatus validation_result = validate_arguments(argc, argv);
    if (validation_result != VALIDATION_SUCCESS)
    {
        handle_validation_error(validation_result);
        print_usage();
        return 1;
    }

    const char *flag = argv[1];
    long long number;

    // Парсинг числа (уже провалидировано)
    validate_number(argv[2], &number);

    // Обработка флагов
    if (strcmp(flag, "-h") == 0 || strcmp(flag, "/h") == 0)
    {
        int *multiples = NULL;
        size_t count = 0;

        OperationStatus result = find_multiples(number, &multiples, &count);

        if (result == OPERATION_SUCCESS)
        {
            printf("Multiples of %lld up to 100: ", number);
            for (size_t i = 0; i < count; i++)
            {
                printf("%d", multiples[i]);
                if (i < count - 1)
                {
                    printf(" ");
                }
            }
            printf("\n");
            free(multiples);
        }
        else if (result == OPERATION_NO_RESULTS)
        {
            printf("No natural numbers up to 100 are multiples of %lld\n", number);
        }
        else
        {
            handle_operation_error(result);
        }
    }
    else if (strcmp(flag, "-p") == 0 || strcmp(flag, "/p") == 0)
    {
        int is_prime, is_composite;

        OperationStatus result = check_prime(number, &is_prime, &is_composite);

        if (result == OPERATION_SUCCESS)
        {
            if (is_prime)
            {
                printf("%lld is a prime number\n", number);
            }
            else if (is_composite)
            {
                printf("%lld is a composite number\n", number);
            }
            else
            {
                printf("%lld is neither prime nor composite\n", number);
            }
        }
        else
        {
            handle_operation_error(result);
        }
    }
    else if (strcmp(flag, "-s") == 0 || strcmp(flag, "/s") == 0)
    {
        char *digits = NULL;
        size_t length = 0;

        OperationStatus result = split_hex_digits(number, &digits, &length);

        if (result == OPERATION_SUCCESS)
        {
            printf("Hexadecimal digits of %lld: %s\n", number, digits);
            free(digits);
        }
        else
        {
            handle_operation_error(result);
        }
    }
    else if (strcmp(flag, "-e") == 0 || strcmp(flag, "/e") == 0)
    {
        OperationStatus result = print_power_table(number);

        if (result != OPERATION_SUCCESS)
        {
            handle_operation_error(result);
        }
    }
    else if (strcmp(flag, "-a") == 0 || strcmp(flag, "/a") == 0)
    {
        unsigned long long sum;

        OperationStatus result = calculate_sum(number, &sum);

        if (result == OPERATION_SUCCESS)
        {
            printf("Sum of natural numbers from 1 to %lld: %llu\n", number, sum);
        }
        else
        {
            handle_operation_error(result);
        }
    }
    else if (strcmp(flag, "-f") == 0 || strcmp(flag, "/f") == 0)
    {
        unsigned long long factorial;

        OperationStatus result = calculate_factorial(number, &factorial);

        if (result == OPERATION_SUCCESS)
        {
            printf("Factorial of %lld: %llu\n", number, factorial);
        }
        else
        {
            handle_operation_error(result);
        }
    }

    return 0;
}