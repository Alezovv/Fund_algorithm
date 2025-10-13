#ifndef FINITE_H
#define FINITE_H

#include <stddef.h>

typedef enum
{
    FIN_OK = 0,
    FIN_INVALID_ARG = 1,
    FIN_NO_APPROX = 2
} fin_status_t;

fin_status_t check_fractions_in_base(int base, double eps, size_t n, ...);

#endif // FINITE_H