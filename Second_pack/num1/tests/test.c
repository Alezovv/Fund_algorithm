#include "../include/finite.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void test_valid_cases()
{
    fin_status_t status;

    status = check_fractions_in_base(2, 1e-12, 3, 0.5, 0.25, 0.125);
    assert(status == FIN_OK);

    status = check_fractions_in_base(10, 1e-12, 3, 0.5, 0.2, 0.25);
    assert(status == FIN_OK);

    printf("test_valid_cases: PASSED\n");
}

void test_invalid_args()
{
    fin_status_t status;

    status = check_fractions_in_base(1, 1e-12, 2, 0.5, 0.25);
    assert(status == FIN_INVALID_ARG);

    status = check_fractions_in_base(10, -1e-6, 1, 0.5);
    assert(status == FIN_INVALID_ARG);

    status = check_fractions_in_base(10, 1e-12, 0);
    assert(status == FIN_INVALID_ARG);

    status = check_fractions_in_base(10, 1e-12, 2, -0.5, 1.5);
    assert(status == FIN_INVALID_ARG);

    printf("test_invalid_args: PASSED\n");
}

void test_no_approx()
{
    fin_status_t status;

    status = check_fractions_in_base(10, 1e-20, 1, M_PI - floor(M_PI));
    assert(status == FIN_NO_APPROX);

    status = check_fractions_in_base(10, 1e-30, 1, 0.123456789012345);
    assert(status == FIN_NO_APPROX);

    printf("test_no_approx: PASSED\n");
}

void test_fraction_types()
{
    fin_status_t status;

    status = check_fractions_in_base(2, 1e-12, 1, 0.1);
    assert(status == FIN_OK);

    status = check_fractions_in_base(10, 1e-12, 1, 1.0 / 3.0);
    assert(status == FIN_OK);

    printf("test_fraction_types: PASSED\n");
}

int main(void)
{
    printf("Running tests...\n\n");

    test_valid_cases();
    test_invalid_args();
    test_no_approx();
    test_fraction_types();

    printf("\nAll tests PASSED!\n");
    return 0;
}
