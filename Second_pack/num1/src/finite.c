#include "finite.h"
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

static long gcd_long(long a, long b)
{
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    while (b != 0)
    {
        long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static int approx_rational_continued_fraction(double x, double eps, long maxq, long *out_p, long *out_q)
{
    if (!(x > 0.0 && x < 1.0) || !(eps > 0.0) || maxq <= 0 || out_p == NULL || out_q == NULL)
    {
        return 0;
    }

    double z = x;
    long a;

    long p0 = 0, q0 = 1;
    long p1 = 1, q1 = 0;

    for (int iter = 0; iter < 200; ++iter)
    {
        a = (long)floor(z);
        if (a > LONG_MAX / (p1 > 0 ? p1 : 1))
            break;
        long p2 = a * p1 + p0;
        long q2 = a * q1 + q0;
        if (q2 <= 0)
            break;

        if (q2 > maxq)
        {
            if (q1 == 0)
                break;
            long k = (maxq - q0) / q1;
            if (k <= 0)
                break;
            long p_final = k * p1 + p0;
            long q_final = k * q1 + q0;
            double approx = (double)p_final / (double)q_final;
            if (fabs(approx - x) <= eps)
            {
                *out_p = p_final;
                *out_q = q_final;
                return 1;
            }
            break;
        }

        double approx = (double)p2 / (double)q2;
        if (fabs(approx - x) <= eps)
        {
            *out_p = p2;
            *out_q = q2;
            return 1;
        }

        if (fabs(z - (double)a) < 1e-18)
        {
            break;
        }

        p0 = p1;
        q0 = q1;
        p1 = p2;
        q1 = q2;
        z = 1.0 / (z - (double)a);
    }

    for (long q = 1; q <= maxq; ++q)
    {
        long p = (long)llround(x * (double)q);
        if (p <= 0 || p >= q)
            continue;
        double approx = (double)p / (double)q;
        if (fabs(approx - x) <= eps)
        {
            *out_p = p;
            *out_q = q;
            return 1;
        }
    }

    return 0;
}

static int denom_has_only_base_primes(long q, int base)
{
    if (q <= 0)
        return 0;
    if (base <= 1)
        return 0;

    int base_primes[64];
    int bp_count = 0;
    int b = base;

    for (int f = 2; f * f <= b; ++f)
    {
        if (b % f == 0)
        {
            base_primes[bp_count++] = f;
            while (b % f == 0)
                b /= f;
        }
    }
    if (b > 1)
    {
        base_primes[bp_count++] = b;
    }

    long tmp = q;
    for (int i = 0; i < bp_count && tmp > 1; ++i)
    {
        int p = base_primes[i];
        while (tmp % p == 0)
            tmp /= p;
    }

    return tmp == 1;
}

fin_status_t check_fractions_in_base(int base, double eps, size_t n, ...)
{
    if (base <= 1 || !(eps > 0.0) || n == 0)
    {
        return FIN_INVALID_ARG;
    }

    va_list ap;
    va_start(ap, n);

    fin_status_t overall = FIN_OK;
    const long MAX_DEN = 1000000L;

    for (size_t i = 0; i < n; ++i)
    {
        double x = va_arg(ap, double);

        if (!(x > 0.0 && x < 1.0))
        {
            printf("%.*g -> ERROR: value out of (0,1) range\n", 17, x);
            overall = FIN_INVALID_ARG;
            continue;
        }

        long p = 0, q = 0;
        int ok = approx_rational_continued_fraction(x, eps, MAX_DEN, &p, &q);
        if (!ok)
        {
            printf("%.*g -> ERROR: cannot approximate as rational within eps=%g and maxden=%ld\n", 17, x, eps, MAX_DEN);
            overall = FIN_NO_APPROX;
            continue;
        }

        long g = gcd_long(p, q);
        p /= g;
        q /= g;

        if (denom_has_only_base_primes(q, base))
        {
            printf("%.*g -> FINITE (approx %ld/%ld)\n", 17, x, p, q);
        }
        else
        {
            printf("%.*g -> INFINITE (approx %ld/%ld)\n", 17, x, p, q);
        }
    }

    va_end(ap);
    return overall;
}