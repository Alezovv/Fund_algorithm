#ifndef PRIME_H
#define PRIME_H

#include <limits.h>

typedef enum
{
    PRIME_SUCCESS,
    PRIME_NUMBER_TOO_LARGE,
    NOT_PRIME
} PrimeStatus;

PrimeStatus FindPrime(int n, long long int *out);

PrimeStatus IsPrime(long long x);

#endif // PRIME_H