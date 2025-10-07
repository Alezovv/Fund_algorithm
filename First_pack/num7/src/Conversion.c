#include "../include/Conversion.h"
#include <string.h>
#include <ctype.h>
#include <limits.h>

ConversionStatus char_to_digit(char c, int *digit)
{
    if (digit == NULL)
    {
        return CONVERSION_INVALID_DIGIT;
    }

    if (c >= '0' && c <= '9')
    {
        *digit = c - '0';
        return CONVERSION_SUCCESS;
    }

    if (c >= 'A' && c <= 'Z')
    {
        *digit = c - 'A' + 10;
        return CONVERSION_SUCCESS;
    }

    if (c >= 'a' && c <= 'z')
    {
        *digit = c - 'a' + 10;
        return CONVERSION_SUCCESS;
    }

    return CONVERSION_INVALID_DIGIT;
}

ConversionStatus convert_to_decimal(const char *str, int base, long long *result)
{
    if (str == NULL || result == NULL)
    {
        return CONVERSION_EMPTY_STRING;
    }

    if (base < 2 || base > 36)
    {
        return CONVERSION_INVALID_BASE;
    }

    size_t len = strlen(str);
    if (len == 0)
    {
        return CONVERSION_EMPTY_STRING;
    }

    long long value = 0;
    int digit;

    for (size_t i = 0; i < len; i++)
    {
        char c = str[i];
        ConversionStatus status = char_to_digit(c, &digit);
        if (status != CONVERSION_SUCCESS)
        {
            return status;
        }

        if (digit >= base)
        {
            return CONVERSION_INVALID_DIGIT;
        }

        // Проверка на переполнение
        if (value > (LLONG_MAX - digit) / base)
        {
            return CONVERSION_OVERFLOW;
        }

        value = value * base + digit;
    }

    *result = value;
    return CONVERSION_SUCCESS;
}

ConversionStatus find_min_base(const char *str, int *min_base)
{
    if (str == NULL || min_base == NULL)
    {
        return CONVERSION_EMPTY_STRING;
    }

    size_t len = strlen(str);
    if (len == 0)
    {
        return CONVERSION_EMPTY_STRING;
    }

    int max_digit = 0;
    int digit;

    // Находим максимальную цифру в числе
    for (size_t i = 0; i < len; i++)
    {
        ConversionStatus status = char_to_digit(str[i], &digit);
        if (status != CONVERSION_SUCCESS)
        {
            return status;
        }

        if (digit > max_digit)
        {
            max_digit = digit;
        }
    }

    // Минимальное основание = max_digit + 1, но не меньше 2
    *min_base = (max_digit + 1 < 2) ? 2 : (max_digit + 1);

    return CONVERSION_SUCCESS;
}

void remove_leading_zeros(char *str)
{
    if (str == NULL)
        return;

    size_t len = strlen(str);
    if (len == 0)
        return;

    // Находим первую ненулевую цифру
    size_t start = 0;
    while (start < len - 1 && str[start] == '0')
    {
        start++;
    }

    // Сдвигаем строку
    if (start > 0)
    {
        memmove(str, str + start, len - start + 1);
    }
}