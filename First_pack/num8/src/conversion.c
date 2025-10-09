#include "../include/conversion.h"
#include <ctype.h>
#include <string.h>
#include <limits.h>

static int char_to_digit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 10;
    return -1;
}

ConversionStatus str_to_ll(const char *str, int base, long long *result)
{
    if (str == NULL || result == NULL)
    {
        return CONVERSION_NULL_POINTER;
    }

    if (base < 2 || base > 36)
    {
        return CONVERSION_INVALID_BASE;
    }

    if (*str == '\0')
    {
        return CONVERSION_INVALID_INPUT;
    }

    int sign = 1;
    const char *ptr = str;

    if (*ptr == '-')
    {
        sign = -1;
        ptr++;
        if (*ptr == '\0')
        {
            return CONVERSION_INVALID_INPUT;
        }
    }

    unsigned long long res = 0;
    const unsigned long long max_positive = (unsigned long long)LLONG_MAX;
    const unsigned long long max_negative = (unsigned long long)LLONG_MAX + 1;

    while (*ptr)
    {
        int digit = char_to_digit(*ptr);
        if (digit < 0 || digit >= base)
        {
            return CONVERSION_INVALID_INPUT;
        }

        if (sign == 1)
        {
            if (res > max_positive / base ||
                (res == max_positive / base && digit > (int)(max_positive % base)))
            {
                return CONVERSION_OVERFLOW;
            }
        }
        else
        {
            if (res > max_negative / base ||
                (res == max_negative / base && digit > (int)(max_negative % base)))
            {
                return CONVERSION_OVERFLOW;
            }
        }

        res = res * base + digit;
        ptr++;
    }

    if (sign == -1)
    {
        if (res == max_negative)
        {
            *result = LLONG_MIN;
        }
        else
        {
            *result = -(long long)res;
        }
    }
    else
    {
        *result = (long long)res;
    }

    return CONVERSION_SUCCESS;
}

ConversionStatus ll_to_str(long long num, int base, char *buffer, size_t buffer_size, char **result_str)
{
    if (buffer == NULL || result_str == NULL)
    {
        return CONVERSION_NULL_POINTER;
    }

    if (base < 2 || base > 36)
    {
        return CONVERSION_INVALID_BASE;
    }

    if (buffer_size < 3)
    {
        return CONVERSION_BUFFER_TOO_SMALL;
    }

    char *ptr = buffer + buffer_size - 1;
    *ptr = '\0';

    int is_negative = 0;
    unsigned long long n;

    if (num < 0)
    {
        is_negative = 1;
        if (num == LLONG_MIN)
        {
            n = (unsigned long long)LLONG_MAX + 1;
        }
        else
        {
            n = (unsigned long long)(-num);
        }
    }
    else
    {
        n = (unsigned long long)num;
    }

    do
    {
        if (ptr <= buffer)
        {
            return CONVERSION_BUFFER_TOO_SMALL;
        }

        unsigned int digit = n % base;
        n /= base;
        *--ptr = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
    } while (n > 0);

    if (is_negative)
    {
        if (ptr <= buffer)
        {
            return CONVERSION_BUFFER_TOO_SMALL;
        }
        *--ptr = '-';
    }

    *result_str = ptr;
    return CONVERSION_SUCCESS;
}