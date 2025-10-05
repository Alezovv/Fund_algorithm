#include <stdio.h>
#include <assert.h>
#include "../include/prime.h"
#include "../include/validation.h"

void test_validate_number_positive()
{
    printf("Testing positive numbers...\n");

    assert(validate_number(1) == VALIDATION_SUCCESS);
    assert(validate_number(1000) == VALIDATION_SUCCESS);
    assert(validate_number(INT_MAX) == VALIDATION_SUCCESS);

    printf("Positive numbers test passed!\n");
}

void test_validate_number_zero()
{
    printf("Testing zero...\n");

    assert(validate_number(0) == VALIDATION_NUMBER_ZERO);

    printf("Zero test passed!\n");
}

void test_validate_number_negative()
{
    printf("Testing negative numbers...\n");

    assert(validate_number(-1) == VALIDATION_NUMBER_TOO_SMALL);
    assert(validate_number(-1000) == VALIDATION_NUMBER_TOO_SMALL);
    assert(validate_number(INT_MIN) == VALIDATION_NUMBER_TOO_SMALL);

    printf("Negative numbers test passed!\n");
}

void test_IsPrime()
{
    printf("Testing IsPrime function...\n");

    assert(IsPrime(2) == PRIME_SUCCESS);
    assert(IsPrime(3) == PRIME_SUCCESS);
    assert(IsPrime(5) == PRIME_SUCCESS);
    assert(IsPrime(23) == PRIME_SUCCESS);
    assert(IsPrime(31) == PRIME_SUCCESS);

    assert(IsPrime(1) == NOT_PRIME);
    assert(IsPrime(4) == NOT_PRIME);
    assert(IsPrime(6) == NOT_PRIME);
    assert(IsPrime(8) == NOT_PRIME);
    assert(IsPrime(9) == NOT_PRIME);

    assert(IsPrime(0) == NOT_PRIME);
    assert(IsPrime(-1) == NOT_PRIME);
    assert(IsPrime(-5) == NOT_PRIME);

    printf("All IsPrime tests passed!\n");
}

void test_FindPrime()
{
    printf("Testing FindPrime function...\n");

    long long result;

    assert(FindPrime(1, &result) == PRIME_SUCCESS && result == 2);
    assert(FindPrime(2, &result) == PRIME_SUCCESS && result == 3);
    assert(FindPrime(3, &result) == PRIME_SUCCESS && result == 5);
    assert(FindPrime(4, &result) == PRIME_SUCCESS && result == 7);
    assert(FindPrime(5, &result) == PRIME_SUCCESS && result == 11);
    assert(FindPrime(6, &result) == PRIME_SUCCESS && result == 13);

    assert(FindPrime(25, &result) == PRIME_SUCCESS && result == 97);
    assert(FindPrime(50, &result) == PRIME_SUCCESS && result == 229);
    assert(FindPrime(100, &result) == PRIME_SUCCESS && result == 541);

    printf("All FindPrime basic tests passed!\n");
}

void test_large_primes()
{
    printf("Testing large primes...\n");

    long long result;

    // Тестируем несколько больших простых чисел
    assert(FindPrime(1000, &result) == PRIME_SUCCESS);
    assert(IsPrime(result) == PRIME_SUCCESS);

    assert(FindPrime(5000, &result) == PRIME_SUCCESS);
    assert(IsPrime(result) == PRIME_SUCCESS);

    printf("Large primes test passed!\n");
}

void run_all_tests()
{
    printf("Running validation tests...\n\n");

    test_validate_number_positive();
    printf("\n");

    test_validate_number_zero();
    printf("\n");

    test_validate_number_negative();
    printf("\n");

    printf("Running prime number tests...\n\n");

    test_IsPrime();
    printf("\n");

    test_FindPrime();
    printf("\n");

    test_large_primes();
    printf("\n");

    printf("All tests passed \n");
}

int main()
{
    run_all_tests();
    return 0;
}