#include <stdio.h>
#include <assert.h>
#include "../include/validation.h"
#include "../include/operations.h"

void test_validation(void)
{
    printf("Testing validation...\n");

    // Тест валидации аргументов
    char *test_args1[] = {"program", "-h", "5"};
    assert(validate_arguments(3, test_args1) == VALIDATION_SUCCESS);

    char *test_args2[] = {"program", "-h"};
    assert(validate_arguments(2, test_args2) == VALIDATION_INVALID_ARGC);

    char *test_args3[] = {"program", "-x", "5"};
    assert(validate_arguments(3, test_args3) == VALIDATION_INVALID_FLAG);

    char *test_args4[] = {"program", "-h", "abc"};
    assert(validate_arguments(3, test_args4) == VALIDATION_INVALID_SYMBOL);

    printf("Validation tests passed!\n");
}

void test_math_operations(void)
{
    printf("Testing math operations...\n");

    // Тест кратных чисел
    int *multiples = NULL;
    size_t count = 0;
    assert(find_multiples(25, &multiples, &count) == OPERATION_SUCCESS);
    assert(count == 4); // 25, 50, 75, 100
    free(multiples);

    // Тест простых чисел
    int is_prime, is_composite;
    assert(check_prime(7, &is_prime, &is_composite) == OPERATION_SUCCESS);
    assert(is_prime == 1);
    assert(is_composite == 0);

    // Тест суммы
    unsigned long long sum;
    assert(calculate_sum(10, &sum) == OPERATION_SUCCESS);
    assert(sum == 55);

    printf("Math operations tests passed!\n");
}

int main(void)
{
    test_validation();
    test_math_operations();
    printf("All tests passed!\n");
    return 0;
}