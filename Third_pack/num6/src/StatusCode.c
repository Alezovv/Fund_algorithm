#include "../include/StatusCode.h"

void print_usage()
{
    printf("Usage: <program name> <string>\n");
    printf("Example: main (<1 + 3> * [5 - 1]{a})\n");
}

void handle_error(StatusCode status)
{
    switch (status)
    {
    case STATUS_STRING_EMPTY:
    {
        printf("Подана пустая строка!\n");
        break;
    }
    case STATUS_ERROR_OVERFLOW:
    {
        printf("Слишком большое количество скобок!\n");
        break;
    }
    case STATUS_ERROR_MEMORY_ALLOCATE:
    {
        printf("Память не выделена!\n");
        break;
    }
    case STATUS_ERROR_NOT_CREATED_STACK:
    {
        printf("Не создан стек!\n");
        break;
    }
    case STATUS_ERROR_EMPTY_STACK:
    {
        printf("Стек пуст!\n");
        break;
    }
    case STATUS_ERROR_WRONG_ARGUMENT:
    {
        printf("Передан неверный аргумент!\n");
        break;
    }
    case STATUS_ERROR_NOT_ENOUGH_BRACKETS:
    {
        printf("Не хватает скобки!\n");
        break;
    }
    default:
    {
        printf("Неопределенная ошибка!\n");
        break;
    }
    }
}
