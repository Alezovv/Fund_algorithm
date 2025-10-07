#include "../include/Validation.h"
#include "../include/Utils.h"
#include "../include/Conversion.h"
#include "../include/FileProcessing.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_char_to_digit()
{
    int digit;
    ConversionStatus status;

    // Тест цифр
    status = char_to_digit('5', &digit);
    assert(status == CONVERSION_SUCCESS && digit == 5);

    // Тест заглавных букв
    status = char_to_digit('A', &digit);
    assert(status == CONVERSION_SUCCESS && digit == 10);

    // Тест строчных букв
    status = char_to_digit('z', &digit);
    assert(status == CONVERSION_SUCCESS && digit == 35);

    // Тест невалидного символа
    status = char_to_digit('@', &digit);
    assert(status == CONVERSION_INVALID_DIGIT);

    printf("test_char_to_digit: PASSED\n");
}

void test_find_min_base()
{
    int base;
    ConversionStatus status;

    // Тест двоичного числа
    status = find_min_base("101", &base);
    assert(status == CONVERSION_SUCCESS && base == 2);

    // Тест шестнадцатеричного числа
    status = find_min_base("1AF", &base);
    assert(status == CONVERSION_SUCCESS && base == 16);

    // Тест максимального основания
    status = find_min_base("Z9", &base);
    assert(status == CONVERSION_SUCCESS && base == 36);

    // Тест единицы
    status = find_min_base("1", &base);
    assert(status == CONVERSION_SUCCESS && base == 2);

    printf("test_find_min_base: PASSED\n");
}

void test_convert_to_decimal()
{
    long long result;
    ConversionStatus status;

    // Тест двоичного числа
    status = convert_to_decimal("101", 2, &result);
    assert(status == CONVERSION_SUCCESS && result == 5);

    // Тест шестнадцатеричного числа
    status = convert_to_decimal("FF", 16, &result);
    assert(status == CONVERSION_SUCCESS && result == 255);

    // Тест с основанием 11
    status = convert_to_decimal("1A", 11, &result);
    assert(status == CONVERSION_SUCCESS && result == 21);

    // Тест невалидной цифры для основания
    status = convert_to_decimal("12", 2, &result);
    assert(status == CONVERSION_INVALID_DIGIT);

    printf("test_convert_to_decimal: PASSED\n");
}

void test_remove_leading_zeros()
{
    char str1[] = "00123";
    char str2[] = "100";
    char str3[] = "0000";
    char str4[] = "0";

    remove_leading_zeros(str1);
    assert(strcmp(str1, "123") == 0);

    remove_leading_zeros(str2);
    assert(strcmp(str2, "100") == 0);

    remove_leading_zeros(str3);
    assert(strcmp(str3, "0") == 0);

    remove_leading_zeros(str4);
    assert(strcmp(str4, "0") == 0);

    printf("test_remove_leading_zeros: PASSED\n");
}

void test_validation()
{
    ValidationStatus status;

    // Тест валидных символов
    status = Validate_Number('5');
    assert(status == VALIDATION_SUCCESS);

    status = Validate_Number('A');
    assert(status == VALIDATION_SUCCESS);

    status = Validate_Number('z');
    assert(status == VALIDATION_SUCCESS);

    // Тест невалидных символов
    status = Validate_Number(' ');
    assert(status == VALIDATION_WRONG_NUMBER);

    status = Validate_Number('@');
    assert(status == VALIDATION_WRONG_NUMBER);

    printf("test_validation: PASSED\n");
}

void test_utils()
{
    // Тест разделителей - isspace возвращает ненулевое значение для пробельных символов
    assert(Is_Sign(' ') != 0);  // пробел
    assert(Is_Sign('\t') != 0); // табуляция
    assert(Is_Sign('\n') != 0); // новая строка
    assert(Is_Sign('A') == 0);  // буква
    assert(Is_Sign('5') == 0);  // цифра
    assert(Is_Sign('@') == 0);  // символ

    printf("test_utils: PASSED\n");
}

int main()
{
    printf("Running tests...\n\n");

    test_char_to_digit();
    test_find_min_base();
    test_convert_to_decimal();
    test_remove_leading_zeros();
    test_validation();
    test_utils();

    printf("\nAll tests PASSED!\n");
    return 0;
}