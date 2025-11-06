#include "../include/Logging.h"

FILE *log_file = NULL;

StatusCode Init_Logger(const char *filename)
{
    if (filename == NULL)
    {
        return WRONG_ARGUMENT;
    }

    log_file = fopen(filename, "w");
    if (log_file == NULL)
    {
        return FILE_ERROR;
    }

    return SUCCESS;
}

void Close_Logger()
{
    if (log_file != NULL)
    {
        fclose(log_file);
        log_file = NULL;
    }
}

const char *Status_Handle(StatusCode status)
{
    switch (status)
    {
    case WRONG_ARGUMENT:
        return "Подана неверная строка\n";
    case MEMORY_ALLOCATE:
        return "Ошибка выделения памяти\n";
    case STACK_EMPTY:
        return "Ошибка работы стека\n";
    case FILE_ERROR:
        return "Ошибка открытия файла\n";
    case DIVISION_BY_ZERO:
        return "Ошибка деления на 0\n";
    default:
        return "Неизвестная ошибка\n";
    }
}

void print_usage()
{
    printf("Вводите команды вида: \n");
    printf("A = 2\n");
    printf("B = A * 3\n");
    printf("print(B)\n");
    printf("Для остановки введите \"exit\"\n");
    printf("Логи лежат в файле \"info.log\"\n");
}