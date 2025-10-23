#include <stdio.h>
#include "finite.h"

int main()
{

    printf("Тесты: основание 2\n");
    check_fractions_in_base(2, 1e-12, 6, 0.5, 0.25, 0.125, 0.1, 0.2, 0.375);

    printf("\nТесты: основание 10\n");
    check_fractions_in_base(10, 1e-12, 6, 0.5, 0.25, 0.125, 0.1, 0.2, 1.0/3);

    printf("\nТесты: основание 6\n");
    check_fractions_in_base(255, 1e-12, 5, 0.5, 0.2, 0.25, 1.0/255, 0.0625);

    return 0;
}