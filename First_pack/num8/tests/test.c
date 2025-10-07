#include "../include/conversion.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

void test_str_to_ll()
{
    long long result;
    ConversionStatus status;

    // Тест простых чисел
    status = str_to_ll("101", 2, &result);
    assert(status == CONVERSION_SUCCESS && result == 5);

    status = str_to_ll("FF", 16, &result);
    assert(status == CONVERSION_SUCCESS && result == 255);

    status = str_to_ll("1A", 16, &result);
    assert(status == CONVERSION_SUCCESS && result == 26);

    // Тест отрицательных чисел
    status = str_to_ll("-10", 10, &result);
    assert(status == CONVERSION_SUCCESS && result == -10);

    status = str_to_ll("-FF", 16, &result);
    assert(status == CONVERSION_SUCCESS && result == -255);

    // Тест невалидного основания
    status = str_to_ll("123", 1, &result);
    assert(status == CONVERSION_INVALID_BASE);

    status = str_to_ll("123", 37, &result);
    assert(status == CONVERSION_INVALID_BASE);

    // Тест невалидного ввода
    status = str_to_ll("12G", 16, &result);
    assert(status == CONVERSION_INVALID_INPUT);

    status = str_to_ll("", 10, &result);
    assert(status == CONVERSION_INVALID_INPUT);

    status = str_to_ll("-", 10, &result);
    assert(status == CONVERSION_INVALID_INPUT);

    // Тест нулевых указателей
    status = str_to_ll(NULL, 10, &result);
    assert(status == CONVERSION_NULL_POINTER);

    status = str_to_ll("123", 10, NULL);
    assert(status == CONVERSION_NULL_POINTER);

    printf("test_str_to_ll: PASSED\n");
}

void test_ll_to_str()
{
    char buffer[100];
    char *result_str;
    ConversionStatus status;

    // Тест положительных чисел
    status = ll_to_str(255, 16, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS && strcmp(result_str, "FF") == 0);

    status = ll_to_str(26, 16, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS && strcmp(result_str, "1A") == 0);

    status = ll_to_str(123, 10, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS && strcmp(result_str, "123") == 0);

    // Тест отрицательных чисел
    status = ll_to_str(-10, 10, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS && strcmp(result_str, "-10") == 0);

    status = ll_to_str(-255, 16, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS && strcmp(result_str, "-FF") == 0);

    // Тест разных систем счисления
    status = ll_to_str(35, 36, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS && strcmp(result_str, "Z") == 0);

    status = ll_to_str(100, 9, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS && strcmp(result_str, "121") == 0);

    // Тест минимального буфера (должен быть достаточно большим для числа)
    status = ll_to_str(123, 10, buffer, 5, &result_str); // "123" + '\0' = 4 байта
    assert(status == CONVERSION_SUCCESS);

    // Тест слишком маленького буфера
    status = ll_to_str(123456, 10, buffer, 3, &result_str);
    assert(status == CONVERSION_BUFFER_TOO_SMALL);

    // Тест невалидного основания
    status = ll_to_str(123, 1, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_INVALID_BASE);

    status = ll_to_str(123, 37, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_INVALID_BASE);

    // Тест нулевых указателей
    status = ll_to_str(123, 10, NULL, sizeof(buffer), &result_str);
    assert(status == CONVERSION_NULL_POINTER);

    status = ll_to_str(123, 10, buffer, sizeof(buffer), NULL);
    assert(status == CONVERSION_NULL_POINTER);

    printf("test_ll_to_str: PASSED\n");
}

void test_edge_cases()
{
    long long result;
    ConversionStatus status;
    char buffer[100];
    char *result_str;

    // Тест максимального значения
    status = str_to_ll("9223372036854775807", 10, &result); // LLONG_MAX
    assert(status == CONVERSION_SUCCESS && result == LLONG_MAX);

    // Тест минимального значения
    status = str_to_ll("-9223372036854775808", 10, &result); // LLONG_MIN
    assert(status == CONVERSION_SUCCESS && result == LLONG_MIN);

    // Тест преобразования максимального значения в разные системы
    status = ll_to_str(LLONG_MAX, 10, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS);
    assert(strcmp(result_str, "9223372036854775807") == 0);

    status = ll_to_str(LLONG_MAX, 16, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS);

    // Тест преобразования минимального значения
    status = ll_to_str(LLONG_MIN, 10, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS);
    assert(strcmp(result_str, "-9223372036854775808") == 0);

    // Тест нуля
    status = str_to_ll("0", 10, &result);
    assert(status == CONVERSION_SUCCESS && result == 0);

    status = ll_to_str(0, 10, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS && strcmp(result_str, "0") == 0);

    status = ll_to_str(0, 16, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS && strcmp(result_str, "0") == 0);

    // Тест чисел близких к границам
    status = str_to_ll("9223372036854775806", 10, &result); // LLONG_MAX - 1
    assert(status == CONVERSION_SUCCESS && result == LLONG_MAX - 1);

    status = str_to_ll("-9223372036854775807", 10, &result); // LLONG_MIN + 1
    assert(status == CONVERSION_SUCCESS && result == LLONG_MIN + 1);

    printf("test_edge_cases: PASSED\n");
}

void test_remove_leading_zeros()
{
    // Эта функция теперь в main.c, но мы можем протестировать логику через преобразования
    char buffer[100];
    char *result_str;
    ConversionStatus status;

    // Тест что функция не добавляет ведущие нули
    status = ll_to_str(5, 10, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS && strcmp(result_str, "5") == 0);

    status = ll_to_str(0, 10, buffer, sizeof(buffer), &result_str);
    assert(status == CONVERSION_SUCCESS && strcmp(result_str, "0") == 0);

    printf("test_remove_leading_zeros: PASSED\n");
}

int main()
{
    printf("Running conversion tests...\n\n");

    test_str_to_ll();
    test_ll_to_str();
    test_edge_cases();
    test_remove_leading_zeros();

    printf("\nAll conversion tests PASSED!\n");
    return 0;
}