#include "../include/Check_Brackets.h"
#include "../include/Stack.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        print_usage();
        printf("Неверное количество аргументов!\n");
        return 1;
    }
    StatusCode status = STATUS_SUCCESS;
    const char *str = argv[1];
    Stack s;
    status = StackInit(&s);
    if (status != STATUS_SUCCESS)
    {
        handle_error(status);
        return 1;
    }

    status = check_brackets(&s, str);
    if (status != STATUS_SUCCESS)
    {
        handle_error(status);
        return 1;
    }

    printf("Проверка удалась! Расстановка скобок верная\n");
    DeleteStack(&s);
    return 0;
}