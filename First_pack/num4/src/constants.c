#include "../include/constants.h"
#include <stdio.h>
#include <math.h>

int is_prime(int n)
{
    if (n < 2)
        return 0;
    if (n == 2)
        return 1;
    if (n % 2 == 0)
        return 0;

    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

double factorial(int n)
{
    double result = 1.0;
    for (int i = 1; i <= n; i++)
        result *= i;
    return result;
}

double power(double x, int n)
{
    double result = 1.0;
    for (int i = 0; i < n; i++)
        result *= x;
    return result;
}

void e_limit(double *result)
{
    int n = MAX_ITERATIONS;
    *result = power((1.0 + 1.0 / n), n);
}

void e_series(double *result)
{
    *result = 0.0;
    for (int n = 0; n < MAX_ITERATIONS; n++)
        *result += 1.0 / factorial(n);
}

void e_equation(double *result)
{
    *result = exp(1.0);
}

ConstStatus calculate_e(Method method, double *result)
{
    if (result == NULL)
        return CONST_ERROR_CALCULATION;

    switch (method)
    {
    case 0:
        e_limit(result);
        return CONST_SUCCESS;
    case 1:
        e_series(result);
        return CONST_SUCCESS;
    case 2:
        e_equation(result);
        return CONST_SUCCESS;
    default:
        return CONST_ERROR_CALCULATION;
    }
}

void pi_limit(double *result)
{
    int n = 40;

    double term1 = power(2, n);
    double term2 = factorial(n);
    double combined = term1 * term2;

    double numerator = power(combined, 4);

    double fact_2n = factorial(2 * n);
    double denumerator = n * power(fact_2n, 2);

    *result = numerator / denumerator;
}

void pi_series(double *result)
{
    *result = 0;
    for (int n = 1; n < MAX_ITERATIONS; n++)
        *result += power(-1, n - 1) / (2 * n - 1);
    *result *= 4;
}

void pi_equation(double *result)
{
    *result = acos(-1.0);
}

ConstStatus calculate_pi(Method method, double *result)
{
    if (result == NULL)
        return CONST_ERROR_CALCULATION;

    switch (method)
    {
    case 0:
        pi_limit(result);
        return CONST_SUCCESS;
    case 1:
        pi_series(result);
        return CONST_SUCCESS;
    case 2:
        pi_equation(result);
        return CONST_SUCCESS;
    default:
        return CONST_ERROR_CALCULATION;
    }
}

void ln2_limit(double *result)
{
    int n = MAX_ITERATIONS;
    *result = n * (pow(2, 1.0 / n) - 1.0);
}

void ln2_series(double *result)
{
    *result = 0.0;
    for (int n = 1; n < MAX_ITERATIONS; n++)
        *result += power(-1, n - 1) / n;
}

void ln2_equation(double *result)
{
    *result = log(2.0);
}

ConstStatus calculate_ln2(Method method, double *result)
{
    if (result == NULL)
        return CONST_ERROR_CALCULATION;

    switch (method)
    {
    case 0:
        ln2_limit(result);
        return CONST_SUCCESS;
    case 1:
        ln2_series(result);
        return CONST_SUCCESS;
    case 2:
        ln2_equation(result);
        return CONST_SUCCESS;
    default:
        return CONST_ERROR_CALCULATION;
    }
}

void sqrt2_limit(double *result)
{
    double x = -0.5;
    for (int n = 1; n < MAX_ITERATIONS; n++)
        x = x - power(x, 2.0) / 2 + 1;
    *result = x;
}

void sqrt2_series(double *result)
{
    *result = 1.0;

    for (int k = 2; k < MAX_ITERATIONS; k++)
        *result *= pow(2, pow(2, -k));
}

void sqrt2_equation(double *result)
{
    *result = sqrt(2);
}

ConstStatus calculate_sqrt2(Method method, double *result)
{
    if (result == NULL)
        return CONST_ERROR_CALCULATION;

    switch (method)
    {
    case 0:
        sqrt2_limit(result);
        return CONST_SUCCESS;
    case 1:
        sqrt2_series(result);
        return CONST_SUCCESS;
    case 2:
        sqrt2_equation(result);
        return CONST_SUCCESS;
    default:
        return CONST_ERROR_CALCULATION;
    }
}

void gamma_limit(double *result)
{
    *result = 0.0;
    int m = 10;

    for (int k = 1; k <= m; k++)
    {
        double binom = factorial(m) / (factorial(k) * factorial(m - k));

        double term = binom * power(-1, k) / k * log(factorial(k));
        *result += term;
    }
}

void gamma_series(double *result)
{
    *result = 0.0;
    double pi;
    pi_series(&pi);

    double chap1 = -(pi * pi) / 6.0;

    double chap2 = 0.0;
    for (int k = 2; k < MAX_ITERATIONS; k++)
    {
        int sqrt_int = (int)sqrt(k);

        double term = 1.0 / (sqrt_int * sqrt_int) - 1.0 / k;
        chap2 += term;
    }

    *result = chap1 + chap2;
}

void gamma_equation(double *result)
{
    double tmp = 1.0;
    int prime_count = 0;

    for (int p = 2; p < MAX_ITERATIONS; p++)
    {
        if (is_prime(p))
        {
            tmp *= (double)(p - 1) / p;
            prime_count++;
        }
    }

    double egam = log(MAX_ITERATIONS) * tmp;
    *result = -log(egam);
}

ConstStatus calculate_gamma(Method method, double *result)
{
    if (result == NULL)
        return CONST_ERROR_CALCULATION;

    switch (method)
    {
    case 0:
        gamma_limit(result);
        return CONST_SUCCESS;
    case 1:
        gamma_series(result);
        return CONST_SUCCESS;
    case 2:
        gamma_equation(result);
        return CONST_SUCCESS;
    default:
        return CONST_ERROR_CALCULATION;
    }
}