#include "../include/operations.h"
#include "../include/validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

static bool compare_double(double a, double b, double epsilon)
{
    return fabs(a - b) < epsilon;
}

OperationStatus solve_quadratic_permutations(double epsilon, double a, double b, double c)
{
    ValidationStatus val_status = validate_epsilon(epsilon);
    if (val_status != VALIDATION_SUCCESS)
    {
        return ERROR_INVALID_EPSILON;
    }

    double coefficients[3] = {a, b, c};
    int permutations[6][3] = {
        {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

    for (int i = 0; i < 6; i++)
    {
        bool is_unique = true;
        for (int j = 0; j < i; j++)
        {
            bool same = true;
            for (int k = 0; k < 3; k++)
            {
                if (!compare_double(
                        coefficients[permutations[i][k]],
                        coefficients[permutations[j][k]],
                        epsilon))
                {
                    same = false;
                    break;
                }
            }
            if (same)
            {
                is_unique = false;
                break;
            }
        }

        if (!is_unique)
            continue;

        double A = coefficients[permutations[i][0]];
        double B = coefficients[permutations[i][1]];
        double C = coefficients[permutations[i][2]];

        printf("Уравнение: %.6fx^2 + %.6fx + %.6f = 0\n", A, B, C);

        if (compare_double(A, 0, epsilon))
        {
            if (compare_double(B, 0, epsilon))
            {
                if (compare_double(C, 0, epsilon))
                {
                    printf("  Бесконечное количество решений\n");
                }
                else
                {
                    printf("  Нет решений\n");
                }
            }
            else
            {
                double x = -C / B;
                printf("  Один корень: x = %.6f\n", x);
            }
        }
        else
        {
            double discriminant = B * B - 4 * A * C;

            if (compare_double(discriminant, 0, epsilon))
            {
                double x = -B / (2 * A);
                printf("  Один корень: x = %.6f\n", x);
            }
            else if (discriminant > 0)
            {
                double sqrt_d = sqrt(discriminant);
                double x1 = (-B + sqrt_d) / (2 * A);
                double x2 = (-B - sqrt_d) / (2 * A);
                printf("  Два корня: x1 = %.6f, x2 = %.6f\n", x1, x2);
            }
            else
            {
                double real = -B / (2 * A);
                double imag = sqrt(-discriminant) / (2 * A);
                printf("  Комплексные корни: %.6f ± %.6fi\n", real, imag);
            }
        }
        printf("\n");
    }

    return SUCCESS;
}

OperationStatus check_multiple(int num1, int num2, bool *is_multiple)
{
    if (num2 == 0)
    {
        return ERROR_INVALID_NUMBER;
    }

    *is_multiple = (num1 % num2 == 0);
    return SUCCESS;
}

OperationStatus check_right_triangle(double epsilon, double a, double b, double c, bool *is_right)
{
    ValidationStatus val_status;

    val_status = validate_epsilon(epsilon);
    if (val_status != VALIDATION_SUCCESS)
    {
        return ERROR_INVALID_EPSILON;
    }

    val_status = validate_positive(a);
    if (val_status != VALIDATION_SUCCESS)
    {
        return ERROR_INVALID_NUMBER;
    }

    val_status = validate_positive(b);
    if (val_status != VALIDATION_SUCCESS)
    {
        return ERROR_INVALID_NUMBER;
    }

    val_status = validate_positive(c);
    if (val_status != VALIDATION_SUCCESS)
    {
        return ERROR_INVALID_NUMBER;
    }

    double sides[3] = {a, b, c};
    for (int i = 0; i < 2; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (sides[i] > sides[j])
            {
                double temp = sides[i];
                sides[i] = sides[j];
                sides[j] = temp;
            }
        }
    }

    double sum_squares = sides[0] * sides[0] + sides[1] * sides[1];
    double hypotenuse_square = sides[2] * sides[2];

    *is_right = compare_double(sum_squares, hypotenuse_square, epsilon * epsilon);
    return SUCCESS;
}