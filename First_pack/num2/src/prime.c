#include "../include/prime.h"
#include <limits.h>

PrimeStatus IsPrime(long long x)
{
    if (x < 2)
        return NOT_PRIME;
    if (x == 2)
        return PRIME_SUCCESS;
    if (x % 2 == 0)
        return NOT_PRIME;

    for (long long i = 3; i <= x / i; i += 2)
    {
        if (x % i == 0)
            return NOT_PRIME;
    }
    return PRIME_SUCCESS;
}

PrimeStatus FindPrime(int n, long long int *out)
{
    if (n == 1)
    {
        *out = 2;
        return PRIME_SUCCESS;
    }
    int count = 1;

    for (long long i = 3; i <= LLONG_MAX && i > 0; i += 2)
    {
        if (IsPrime(i) == PRIME_SUCCESS)
        {
            count++;
            if (count == n)
            {
                *out = i;
                return PRIME_SUCCESS;
            }
        }

        if (i >= LLONG_MAX - 2)
        {
            break;
        }
    }
    return PRIME_NUMBER_TOO_LARGE;
}