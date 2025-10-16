#include <stdio.h>
#include "finite.h"

int main(void)
{

    printf("=== Тесты: основание = 2 (двоичная система) ===\n");
    check_fractions_in_base(2, 1e-12, 6, 0.5, 0.25, 0.125, 0.1, 0.2, 0.375);

    printf("\n=== Тесты: основание = 10 (десятичная система) ===\n");
    check_fractions_in_base(10, 1e-12, 6, 0.5, 0.25, 0.125, 0.1, 0.2, 0.3333333333333);

    printf("\n=== Тесты: основание = 6 ===\n");
    check_fractions_in_base(6, 1e-12, 5, 0.5, 0.2, 0.25, 0.1, 0.0625);

    return 0;
}