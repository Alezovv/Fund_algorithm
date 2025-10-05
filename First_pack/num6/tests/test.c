#include "../include/function.h"
#include "../include/validation.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>

void test_validation()
{
    printf("Testing validation...\n");

    // Тест валидации аргументов
    char *valid_args[] = {"program", "a", "0.001"};
    char *invalid_argc[] = {"program", "a"};
    char *invalid_letter[] = {"program", "x", "0.001"};
    char *invalid_epsilon[] = {"program", "a", "invalid"};
    char *out_of_range_epsilon[] = {"program", "a", "1.5"};

    assert(validate_arguments(3, valid_args) == VALIDATION_SUCCESS);
    assert(validate_arguments(2, invalid_argc) == VALIDATION_INVALID_ARGUMENTS);
    assert(validate_arguments(3, invalid_letter) == VALIDATION_INVALID_LETTER);
    assert(validate_arguments(3, invalid_epsilon) == VALIDATION_INVALID_EPSILON);
    assert(validate_arguments(3, out_of_range_epsilon) == VALIDATION_INVALID_EPSILON);

    printf("Validation tests passed\n\n");
}

void test_epsilon_validation()
{
    printf("Testing epsilon validation...\n");

    assert(validate_epsilon("0.001") == VALIDATION_SUCCESS);
    assert(validate_epsilon("0.1") == VALIDATION_SUCCESS);
    assert(validate_epsilon("0.0000001") == VALIDATION_SUCCESS);
    assert(validate_epsilon("0") == VALIDATION_INVALID_EPSILON);
    assert(validate_epsilon("-0.1") == VALIDATION_INVALID_EPSILON);
    assert(validate_epsilon("1.0") == VALIDATION_INVALID_EPSILON);
    assert(validate_epsilon("abc") == VALIDATION_INVALID_EPSILON);
    assert(validate_epsilon("0.001abc") == VALIDATION_INVALID_EPSILON);

    printf("Epsilon validation tests passed\n\n");
}

void test_letter_validation()
{
    printf("Testing letter validation...\n");

    assert(validate_letter("a") == VALIDATION_SUCCESS);
    assert(validate_letter("b") == VALIDATION_SUCCESS);
    assert(validate_letter("c") == VALIDATION_SUCCESS);
    assert(validate_letter("d") == VALIDATION_SUCCESS);
    assert(validate_letter("x") == VALIDATION_INVALID_LETTER);
    assert(validate_letter("A") == VALIDATION_INVALID_LETTER);
    assert(validate_letter("ab") == VALIDATION_INVALID_LETTER);
    assert(validate_letter("") == VALIDATION_INVALID_LETTER);

    printf("Letter validation tests passed\n\n");
}

void test_function_a()
{
    printf("Testing function a (log(1+x)/x)...\n");

    // Проверяем предел в точке x=0
    double result = func_a(0.0);
    assert(fabs(result - 1.0) < 1e-10); // lim(x->0) log(1+x)/x = 1

    // Проверяем другие точки
    assert(fabs(func_a(0.5) - log(1.5) / 0.5) < 1e-10);
    assert(fabs(func_a(1.0) - log(2.0)) < 1e-10);

    // Проверяем интегрирование с разной точностью
    double integral_high_precision = integral(func_a, 0.0001);

    // Значение интеграла ∫₀¹ ln(1+x)/x dx = π²/12 ≈ 0.8224670334241132
    double expected = 0.8224670334241132;
    assert(fabs(integral_high_precision - expected) < 0.001);

    printf("Function a tests passed\n\n");
}

void test_function_b()
{
    printf("Testing function b (exp(-x²/2))...\n");

    // Проверяем значения в точках
    assert(fabs(func_b(0.0) - 1.0) < 1e-10);
    assert(fabs(func_b(1.0) - exp(-0.5)) < 1e-10);

    // Проверяем интегрирование
    double result = integral(func_b, 0.0001);

    // Значение должно быть положительным и меньше 1
    assert(result > 0 && result < 1.0);

    // Проверяем сходимость при разных epsilon
    double result1 = integral(func_b, 0.01);
    double result2 = integral(func_b, 0.0001);
    assert(fabs(result1 - result2) < 0.01); // Должны быть близки

    printf("Function b tests passed\n\n");
}

void test_function_c()
{
    printf("Testing function c (log(1/(1-x)))...\n");

    // Проверяем значения в точках (избегая x=1)
    assert(fabs(func_c(0.0) - 0.0) < 1e-10);
    assert(fabs(func_c(0.5) - log(2.0)) < 1e-10);

    // Проверяем интегрирование
    double result = integral(func_c, 0.0001);

    // Значение должно быть положительным
    assert(result > 0);

    printf("Function c tests passed\n\n");
}

void test_function_d()
{
    printf("Testing function d (x^x)...\n");

    // Проверяем значения в точках
    assert(fabs(func_d(0.1) - pow(0.1, 0.1)) < 1e-10);
    assert(fabs(func_d(0.5) - pow(0.5, 0.5)) < 1e-10);
    assert(fabs(func_d(1.0) - 1.0) < 1e-10);

    // Проверяем интегрирование
    double result = integral(func_d, 0.0001);

    // Значение должно быть между 0 и 1
    assert(result > 0 && result < 1.0);

    printf("Function d tests passed\n\n");
}

void test_integral_precision()
{
    printf("Testing integral precision...\n");

    // Проверяем, что уменьшение epsilon улучшает точность
    double result_low = integral(func_a, 0.01);
    double result_high = integral(func_a, 0.0001);

    // Более точный результат должен быть ближе к известному значению
    double expected = 0.8224670334241132;
    double error_low = fabs(result_low - expected);
    double error_high = fabs(result_high - expected);

    assert(error_high <= error_low); // Ошибка должна уменьшаться или оставаться такой же

    printf("Integral precision tests passed\n\n");
}

void run_all_tests()
{
    printf("Running integral calculator tests...\n\n");

    test_validation();
    test_epsilon_validation();
    test_letter_validation();
    test_function_a();
    test_function_b();
    test_function_c();
    test_function_d();
    test_integral_precision();

    printf("\nAll tests passed!\n");
}

int main()
{
    run_all_tests();
    return 0;
}