#include "../include/ToBase.h"
#include "../include/Arr.h"

int main()
{
    int number = 0;
    printf("Введите число: \n");
    if (scanf("%d", &number) != 1)
    {
        printf("Введено не число!\n");
        return 1;
    }

    print_table(number);

    return 0;
}