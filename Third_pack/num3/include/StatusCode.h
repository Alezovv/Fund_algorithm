#ifndef STATUSCODE_H
#define STATUSCODE_H
#define CHECK                  \
    if (status != SUCCESS)     \
    {                          \
        status_handle(status); \
        return 1;              \
    }

typedef enum
{
    SUCCESS = 0,
    WRONG_ARGUMENT,
    FILE_ERROR,
    LIST_NOT_INITIALIZED,
    SCAN_ERROR
} StatusCode;

void status_handle(StatusCode status)
{
    switch (status)
    {
    case WRONG_ARGUMENT:
    {
        printf("Введен неверный аргумент!\n");
        break;
    }
    case FILE_ERROR:
    {
        printf("Ошибка работы с файлом!\n");
        break;
    }
    case LIST_NOT_INITIALIZED:
    {
        printf("Ошибка при работе со списком!\n");
        break;
    }
    case SCAN_ERROR:
    {
        printf("Ошибка при запросе данных!\n");
        break;
    }
    default:
    {
        printf("Неопознанная ошибка!\n");
        break;
    }
    }
}

#endif // STATUSCODE_H