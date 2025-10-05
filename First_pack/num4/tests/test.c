#include "../include/constants.h"
#include "../include/validation.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define M_E 2.718281828459045
#define M_PI 3.141592653589793

void test_validation()
{
    printf("Testing validation...\n");

    assert(validate_precision(10) == VALIDATION_SUCCESS);
    assert(validate_precision(0) == VALIDATION_INVALID_PRECISION);
    assert(validate_precision(30) == VALIDATION_INVALID_PRECISION);
    assert(validate_method(0) == VALIDATION_SUCCESS);
    assert(validate_method(1) == VALIDATION_SUCCESS);
    assert(validate_method(3) == VALIDATION_INVALID_METHOD);

    printf("Validation tests passed\n\n");
}

void test_e_calculation()
{
    printf("Testing e calculation...\n");

    double result;

    assert(calculate_e(METHOD_LIMITS, &result) == CONST_SUCCESS);
    assert(fabs(result - 2.71828) < 0.1);

    assert(calculate_e(METHOD_SERIES, &result) == CONST_SUCCESS);
    assert(fabs(result - 2.71828) < 0.001);

    assert(calculate_e(METHOD_EQUATION, &result) == CONST_SUCCESS);
    assert(fabs(result - M_E) < 1e-10);

    printf("e calculation tests passed\n\n");
}

void test_pi_calculation()
{
    printf("Testing pi calculation...\n");

    double result;

    assert(calculate_pi(METHOD_LIMITS, &result) == CONST_SUCCESS);
    assert(fabs(result - 3.14159) < 0.1);

    assert(calculate_pi(METHOD_SERIES, &result) == CONST_SUCCESS);
    assert(fabs(result - 3.14159) < 0.01);

    assert(calculate_pi(METHOD_EQUATION, &result) == CONST_SUCCESS);
    assert(fabs(result - M_PI) < 1e-10);

    printf("pi calculation tests passed\n\n");
}

void test_ln2_calculation()
{
    printf("Testing ln2 calculation...\n");

    double result;

    assert(calculate_ln2(METHOD_LIMITS, &result) == CONST_SUCCESS);
    assert(fabs(result - 0.693147) < 0.01);

    assert(calculate_ln2(METHOD_SERIES, &result) == CONST_SUCCESS);
    assert(fabs(result - 0.693147) < 0.001);

    assert(calculate_ln2(METHOD_EQUATION, &result) == CONST_SUCCESS);
    assert(fabs(result - log(2)) < 1e-10);

    printf("ln2 calculation tests passed\n\n");
}

void test_error_conditions()
{
    printf("Testing error conditions...\n");

    double result;

    assert(calculate_e(METHOD_LIMITS, NULL) == CONST_ERROR_CALCULATION);

    assert(calculate_e((Method)5, &result) == CONST_ERROR_CALCULATION);

    printf("Error condition tests passed\n\n");
}

void run_all_tests()
{
    printf("Running constants tests...\n\n");

    test_validation();
    test_e_calculation();
    test_pi_calculation();
    test_ln2_calculation();
    test_error_conditions();

    printf("\nAll tests passed!\n");
}

int main()
{
    run_all_tests();
    return 0;
}