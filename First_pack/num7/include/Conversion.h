#ifndef CONVERSION_H
#define CONVERSION_H

#include <stdio.h>

typedef enum
{
    CONVERSION_SUCCESS = 0,
    CONVERSION_INVALID_BASE,
    CONVERSION_INVALID_DIGIT,
    CONVERSION_OVERFLOW,
    CONVERSION_EMPTY_STRING
} ConversionStatus;

// Конвертирует символ в числовое значение
ConversionStatus char_to_digit(char c, int *digit);

// Конвертирует число из строки в заданной системе счисления в long long
ConversionStatus convert_to_decimal(const char *str, int base, long long *result);

// Находит минимальное основание системы счисления для строки
ConversionStatus find_min_base(const char *str, int *min_base);

// Удаляет ведущие нули из строки
void remove_leading_zeros(char *str);

#endif