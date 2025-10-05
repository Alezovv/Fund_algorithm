#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_ITERATIONS 1000

typedef enum
{
    CONST_SUCCESS = 0,
    CONST_ERROR_CALCULATION
} ConstStatus;

typedef enum
{
    METHOD_LIMITS = 0,
    METHOD_SERIES,
    METHOD_EQUATION
} Method;

// e
void e_limit(double *result);
void e_series(double *result);
void e_equation(double *result);
ConstStatus calculate_e(Method method, double *result);

// pi
void pi_limit(double *result);
void pi_series(double *result);
void pi_equation(double *result);
ConstStatus calculate_pi(Method method, double *result);

// ln2
void ln2_limit(double *result);
void ln2_series(double *result);
void ln2_equation(double *result);
ConstStatus calculate_ln2(Method method, double *result);

// sqrt2
void sqrt2_limit(double *result);
void sqrt2_series(double *result);
void sqrt2_equation(double *result);
ConstStatus calculate_sqrt2(Method method, double *result);

// gamma
void gamma_limit(double *result);
void gamma_series(double *result);
void gamma_equation(double *result);
ConstStatus calculate_gamma(Method method, double *result);

double factorial(int n);
double power(double x, int n);
int is_prime(int n);

#endif // CONSTANTS_H