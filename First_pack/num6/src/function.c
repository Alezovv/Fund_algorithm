#include "../include/function.h"

double func_a(double x)
{
    if (fabs(x) < 1e-15)
        return 1.0;
    return log(1 + x) / x;
}

double func_b(double x)
{
    return exp(-pow(x, 2.0) / 2);
}

double func_c(double x)
{
    if (x > 0.999999)
        return 0.0;
    return log(1 / (1 - x));
}

double func_d(double x)
{
    return pow(x, x);
}

double integral(double (*f)(double), double e)
{
    int n = 1;
    double a = 0.0;
    double b = 1.0;
    double h = (b - a) / n;
    double I_old = (f(a) + f(b)) * h / 2.0;
    double I_new;
    int max_iter = 1000000;

    do
    {
        n *= 2;
        h = (b - a) / n;
        I_new = I_old / 2.0;

        double sum = 0.0;
        for (int i = 1; i < n; i += 2)
        {
            sum += f(a + i * h);
        }
        I_new += sum * h;

        if (fabs(I_new - I_old) < e)
            break;
        I_old = I_new;

    } while (n < max_iter);

    if (n >= max_iter)
    {
        printf("Warning: maximum iterations reached. Precision may be insufficient.\n");
    }

    return I_new;
}