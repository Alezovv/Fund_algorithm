#include "../include/operations.h"
#include "../include/validation.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

void test_validation()
{
    printf("Testing validation...\n");

    int result;
    assert(validate_epsilon(0.0001) == VALIDATION_SUCCESS);
    assert(validate_epsilon(0) == VALIDATION_INVALID_EPSILON);
    assert(validate_number("123", &result) == VALIDATION_SUCCESS);
    assert(validate_number("abc", &result) == VALIDATION_INVALID_NUMBER);
    assert(validate_positive(1.0) == VALIDATION_SUCCESS);
    assert(validate_positive(-1.0) == VALIDATION_NON_POSITIVE);

    printf("Validation tests passed\n");
}

void test_multiple()
{
    printf("Testing multiple check...\n");

    bool is_multiple;

    assert(check_multiple(15, 3, &is_multiple) == SUCCESS && is_multiple == true);
    assert(check_multiple(15, 4, &is_multiple) == SUCCESS && is_multiple == false);
    assert(check_multiple(10, 0, &is_multiple) == ERROR_INVALID_NUMBER);

    printf("Multiple tests passed\n");
}

void test_right_triangle()
{
    printf("Testing right triangle check...\n");

    bool is_right;
    double epsilon = 0.0001;

    assert(check_right_triangle(epsilon, 3, 4, 5, &is_right) == SUCCESS && is_right == true);
    assert(check_right_triangle(epsilon, 3, 4, 6, &is_right) == SUCCESS && is_right == false);
    assert(check_right_triangle(0, 3, 4, 5, &is_right) == ERROR_INVALID_EPSILON);

    printf("Right triangle tests passed\n");
}

void test_quadratic()
{
    printf("Testing quadratic equations...\n");

    // Основные тесты без проверки вывода
    assert(solve_quadratic_permutations(0.0001, 1, -3, 2) == SUCCESS);
    assert(solve_quadratic_permutations(0.0001, 1, 0, 1) == SUCCESS);
    assert(solve_quadratic_permutations(0, 1, -3, 2) == ERROR_INVALID_EPSILON);

    printf("Quadratic tests passed\n");
}

void test_integration()
{
    printf("Testing integration...\n");

    // Тест полного цикла для -m
    int num1, num2;
    assert(validate_number("15", &num1) == VALIDATION_SUCCESS);
    assert(validate_number("3", &num2) == VALIDATION_SUCCESS);

    bool is_multiple;
    assert(check_multiple(num1, num2, &is_multiple) == SUCCESS && is_multiple == true);

    printf("Integration tests passed\n");
}

void run_all_tests()
{
    printf("Running tests...\n\n");

    test_validation();
    test_multiple();
    test_right_triangle();
    test_quadratic();
    test_integration();

    printf("\nAll tests passed!\n");
}

int main()
{
    run_all_tests();
    return 0;
}