#include "../include/validation.h"
#include "../include/prime.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_usage(void)
{
    printf("Usage: <count> <number1> <number2> ... <numberN>\n");
    printf("Example: 3 42 -15 100\n");
}

void handle_validation_error(ValidationStatus status)
{
    switch (status)
    {
    case VALIDATION_NUMBER_TOO_SMALL:
        printf("Error: Number must be positive\n");
        break;
    case VALIDATION_NUMBER_ZERO:
        printf("Error: Number must be not a zero\n");
        break;
    default:
        printf("Error: Unknown validation error\n");
        break;
    }
}

void handle_prime_error(PrimeStatus status)
{
    switch (status)
    {
    case PRIME_NUMBER_TOO_LARGE:
        printf("Error: The number should be less\n");
        break;
    default:
        printf("Error: Unknown validation error\n");
        break;
    }
}

bool Valid_Input(int *tmp)
{
    if (scanf("%d", tmp) != 1)
    {
        printf("Error: invalid input for count\n");
        print_usage();
        return false;
    }

    ValidationStatus val_status = validate_number(*tmp);
    if (val_status != VALIDATION_SUCCESS)
    {
        handle_validation_error(val_status);
        print_usage();
        return false;
    }
    return true;
}

int main()
{
    int count;
    printf("Enter the number of numbers: \n");
    if (!Valid_Input(&count))
        return 1;

    int *queue = malloc(count * sizeof(int));
    long long *doneq = malloc(count * sizeof(long long));
    if (queue == NULL || doneq == NULL)
    {
        printf("Error: Memory allocation failed\n");
        free(queue);
        free(doneq);
        return 1;
    }

    for (int i = 0; i < count; i++)
    {
        printf("Input number(%d): ", i + 1);
        if (!Valid_Input(&queue[i]))
        {
            free(queue);
            free(doneq);
            return 1;
        }

        PrimeStatus status = FindPrime(queue[i], &doneq[i]);
        if (status != PRIME_SUCCESS)
        {
            handle_prime_error(status);
            print_usage();
            free(queue);
            free(doneq);
            return 1;
        }
    }

    printf("\n");
    for (int i = 0; i < count; i++)
        printf("%d: %lld\n", queue[i], doneq[i]);

    free(queue);
    free(doneq);
    return 0;
}