#include "../include/operations.h"

OperationStatus find_multiples(long long x, int **results, size_t *count)
{
    if (x <= 0 || results == NULL || count == NULL)
    {
        return OPERATION_INVALID_INPUT;
    }

    *count = 0;

    for (int i = x; i <= 100; i += x)
    {
        if (i % x == 0)
        {
            (*count)++;
        }
    }

    if (*count == 0)
    {
        return OPERATION_NO_RESULTS;
    }

    *results = (int *)malloc(*count * sizeof(int));
    if (*results == NULL)
    {
        return OPERATION_OVERFLOW;
    }

    size_t index = 0;
    for (int i = x; i <= 100; i += x)
    {
        if (i % x == 0)
        {
            (*results)[index++] = i;
        }
    }

    return OPERATION_SUCCESS;
}

OperationStatus check_prime(long long x, int *is_prime, int *is_composite)
{
    if (x <= 1 || is_prime == NULL || is_composite == NULL)
    {
        return OPERATION_INVALID_INPUT;
    }

    *is_prime = 1;
    *is_composite = 0;

    if (x == 1)
    {
        *is_prime = 0;
        *is_composite = 0;
        return OPERATION_SUCCESS;
    }

    if (x == 2)
    {
        return OPERATION_SUCCESS;
    }

    if (x % 2 == 0)
    {
        *is_prime = 0;
        *is_composite = 1;
        return OPERATION_SUCCESS;
    }

    for (long long i = 3; i * i <= x; i += 2)
    {
        if (x % i == 0)
        {
            *is_prime = 0;
            *is_composite = 1;
            return OPERATION_SUCCESS;
        }
    }

    return OPERATION_SUCCESS;
}

OperationStatus split_hex_digits(long long x, char **result, size_t *length)
{
    if (x < 0 || result == NULL || length == NULL)
    {
        return OPERATION_INVALID_INPUT;
    }

    if (x == 0)
    {
        *result = (char *)malloc(2);
        if (*result == NULL)
        {
            return OPERATION_OVERFLOW;
        }
        (*result)[0] = '0';
        (*result)[1] = '\0';
        *length = 1;
        return OPERATION_SUCCESS;
    }

    // Определяем количество цифр
    long long temp = x;
    size_t digit_count = 0;

    while (temp > 0)
    {
        digit_count++;
        temp /= 16;
    }

    *result = (char *)malloc(digit_count * 2);
    if (*result == NULL)
    {
        return OPERATION_OVERFLOW;
    }

    temp = x;
    size_t pos = digit_count * 2 - 2;

    while (temp > 0)
    {
        int digit = temp % 16;
        char digit_char;

        if (digit < 10)
        {
            digit_char = '0' + digit;
        }
        else
        {
            digit_char = 'A' + (digit - 10);
        }

        (*result)[pos] = digit_char;

        if (pos > 0)
        {
            (*result)[pos - 1] = ' ';
        }

        pos -= 2;
        temp /= 16;
    }

    (*result)[digit_count * 2 - 1] = '\0';
    *length = digit_count * 2 - 1;

    return OPERATION_SUCCESS;
}

OperationStatus print_power_table(long long x)
{
    if (x <= 0 || x > 10)
    {
        return OPERATION_OUT_OF_RANGE;
    }

    printf("Power table for bases 1-10 and exponents 1-%lld:\n", x);
    printf("Base\\Exp");

    for (long long exp = 1; exp <= x; exp++)
    {
        printf("\t%lld", exp);
    }
    printf("\n");

    for (long long base = 1; base <= 10; base++)
    {
        printf("%lld", base);

        for (long long exp = 1; exp <= x; exp++)
        {
            unsigned long long result = 1;
            int overflow = 0;

            for (long long i = 0; i < exp; i++)
            {
                if (result > ULLONG_MAX / base)
                {
                    overflow = 1;
                    break;
                }
                result *= base;
            }

            if (overflow)
            {
                printf("\toverflow");
            }
            else
            {
                printf("\t%llu", result);
            }
        }
        printf("\n");
    }

    return OPERATION_SUCCESS;
}

OperationStatus calculate_sum(long long x, unsigned long long *result)
{
    if (x <= 0 || result == NULL)
    {
        return OPERATION_INVALID_INPUT;
    }

    if (x > 0 && (unsigned long long)x > (ULLONG_MAX * 2) / (x + 1))
    {
        return OPERATION_OVERFLOW;
    }

    *result = (unsigned long long)x * (x + 1) / 2;
    return OPERATION_SUCCESS;
}

OperationStatus calculate_factorial(long long x, unsigned long long *result)
{
    if (x < 0 || result == NULL)
    {
        return OPERATION_INVALID_INPUT;
    }

    if (x == 0)
    {
        *result = 1;
        return OPERATION_SUCCESS;
    }

    unsigned long long fact = 1;

    for (long long i = 1; i <= x; i++)
    {
        if (fact > ULLONG_MAX / i)
        {
            return OPERATION_OVERFLOW;
        }
        fact *= i;
    }

    *result = fact;
    return OPERATION_SUCCESS;
}