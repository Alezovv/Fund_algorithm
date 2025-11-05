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
        return "Подана неверная строка";
    case MEMORY_ALLOCATE:
        return "Ошибка выделения памяти";
    case STACK_EMPTY:
        return "Ошибка работы стека";
    case FILE_ERROR:
        return "Ошибка открытия файла";
    default:
        return "Неизвестная ошибка";
    }
}