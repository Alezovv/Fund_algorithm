#include "../include/operations.h"
#include "../include/validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static void print_usage(const char *program_name)
{
    printf("Использование:\n");
    printf("  %s -q <epsilon> <a> <b> <c>\n", program_name);
    printf("  %s -m <num1> <num2>\n", program_name);
    printf("  %s -t <epsilon> <a> <b> <c>\n", program_name);
}

static void handle_error(OperationStatus status)
{
    switch (status)
    {
    case ERROR_INVALID_ARGUMENTS:
        printf("Ошибка: неверное количество аргументов\n");
        break;
    case ERROR_INVALID_EPSILON:
        printf("Ошибка: epsilon должен быть в диапазоне (0, 1)\n");
        break;
    case ERROR_INVALID_NUMBER:
        printf("Ошибка: неверное число\n");
        break;
    case ERROR_NOT_MULTIPLE:
        printf("Ошибка: числа не кратны\n");
        break;
    case ERROR_NOT_RIGHT_TRIANGLE:
        printf("Ошибка: не прямоугольный треугольник\n");
        break;
    default:
        printf("Неизвестная ошибка\n");
        break;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage(argv[0]);
        return 1;
    }

    const char *flag = argv[1];
    if ((flag[0] != '-' && flag[0] != '/') || flag[1] == '\0' || flag[2] != '\0')
    {
        printf("Ошибка: неверный формат флага\n");
        print_usage(argv[0]);
        return 1;
    }

    char actual_flag = flag[1];
    OperationStatus status;
    ValidationStatus val_status;

    switch (actual_flag)
    {
    case 'q':
    {
        if (argc != 6)
        {
            printf("Ошибка: для -q требуется 5 аргументов\n");
            print_usage(argv[0]);
            return 1;
        }

        double epsilon = atof(argv[2]);
        double a = atof(argv[3]);
        double b = atof(argv[4]);
        double c = atof(argv[5]);

        status = solve_quadratic_permutations(epsilon, a, b, c);
        if (status != SUCCESS)
        {
            handle_error(status);
            return 1;
        }
        break;
    }

    case 'm':
    {
        if (argc != 4)
        {
            printf("Ошибка: для -m требуется 3 аргумента\n");
            print_usage(argv[0]);
            return 1;
        }

        int num1, num2;
        val_status = validate_number(argv[2], &num1);
        if (val_status != VALIDATION_SUCCESS)
        {
            printf("Ошибка: неверное первое число\n");
            return 1;
        }

        val_status = validate_number(argv[3], &num2);
        if (val_status != VALIDATION_SUCCESS)
        {
            printf("Ошибка: неверное второе число\n");
            return 1;
        }

        bool is_multiple;
        status = check_multiple(num1, num2, &is_multiple);
        if (status != SUCCESS)
        {
            handle_error(status);
            return 1;
        }

        printf("Число %d %s кратно %d\n",
               num1, is_multiple ? "" : "не", num2);
        break;
    }

    case 't':
    {
        if (argc != 6)
        {
            printf("Ошибка: для -t требуется 5 аргументов\n");
            print_usage(argv[0]);
            return 1;
        }

        double epsilon = atof(argv[2]);
        double a = atof(argv[3]);
        double b = atof(argv[4]);
        double c = atof(argv[5]);

        bool is_right;
        status = check_right_triangle(epsilon, a, b, c, &is_right);
        if (status != SUCCESS)
        {
            handle_error(status);
            return 1;
        }

        printf("Треугольник со сторонами %.2f, %.2f, %.2f %s прямоугольным\n",
               a, b, c, is_right ? "является" : "не является");
        break;
    }

    default:
        printf("Ошибка: неизвестный флаг '%c'\n", actual_flag);
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}