#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/conversion.h"

static void remove_leading_zeros(char *str)
{
    if (str == NULL || *str == '\0')
        return;

    char *src = str;
    char *dst = str;
    int is_negative = 0;

    if (*src == '-')
    {
        is_negative = 1;
        *dst++ = *src++;
    }

    while (*src == '0' && *(src + 1) != '\0')
    {
        src++;
    }

    while (*src)
    {
        *dst++ = *src++;
    }
    *dst = '\0';

    if (is_negative && dst == str + 1 && *str == '-')
    {
        str[0] = '0';
        str[1] = '\0';
    }
}

static long long llabs_safe(long long num)
{
    if (num == LLONG_MIN)
    {
        return LLONG_MAX;
    }
    return llabs(num);
}

int main(void)
{
    int base;
    printf("Enter base (2-36): ");

    if (scanf("%d", &base) != 1)
    {
        fprintf(stderr, "Error reading base\n");
        return 1;
    }

    if (base < 2 || base > 36)
    {
        fprintf(stderr, "Invalid base: must be between 2 and 36\n");
        return 1;
    }

    long long max_abs_value = 0;
    int has_numbers = 0;
    char max_str[100] = "";
    char input[100];

    printf("Enter numbers (type 'Stop' to finish):\n");

    while (1)
    {
        if (scanf("%99s", input) != 1)
        {
            fprintf(stderr, "Error reading input\n");
            break;
        }

        if (strcmp(input, "Stop") == 0)
        {
            break;
        }

        long long num;
        ConversionStatus status = str_to_ll(input, base, &num);

        switch (status)
        {
        case CONVERSION_SUCCESS:
        {
            long long abs_num = llabs_safe(num);
            long long current_max_abs = llabs_safe(max_abs_value);

            if (!has_numbers || abs_num > current_max_abs)
            {
                max_abs_value = num;
                strncpy(max_str, input, sizeof(max_str) - 1);
                max_str[sizeof(max_str) - 1] = '\0';
                has_numbers = 1;
            }
        }
        break;

        case CONVERSION_INVALID_INPUT:
            fprintf(stderr, "Invalid input: %s\n", input);
            break;

        case CONVERSION_OVERFLOW:
            fprintf(stderr, "Overflow in number: %s\n", input);
            break;

        case CONVERSION_INVALID_BASE:
            fprintf(stderr, "Invalid base for number: %s\n", input);
            break;

        default:
            fprintf(stderr, "Conversion error for: %s\n", input);
            break;
        }
    }

    if (has_numbers)
    {
        remove_leading_zeros(max_str);

        printf("\nMax absolute value: %s\n", max_str);

        int bases[] = {9, 18, 27, 36};
        char buf[100];
        char *result_str;

        for (int i = 0; i < 4; i++)
        {
            ConversionStatus status = ll_to_str(max_abs_value, bases[i], buf, sizeof(buf), &result_str);

            switch (status)
            {
            case CONVERSION_SUCCESS:
                printf("Base %2d: %s\n", bases[i], result_str);
                break;

            case CONVERSION_BUFFER_TOO_SMALL:
                fprintf(stderr, "Buffer too small for base %d conversion\n", bases[i]);
                break;

            case CONVERSION_INVALID_BASE:
                fprintf(stderr, "Invalid base %d\n", bases[i]);
                break;

            default:
                fprintf(stderr, "Conversion error for base %d\n", bases[i]);
                break;
            }
        }
    }
    else
    {
        printf("No valid numbers entered\n");
    }

    return 0;
}