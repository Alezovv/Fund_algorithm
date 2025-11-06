#include "../include/log.h"

FILE *log_file = NULL;

StatusCode Init_Logger(const char *filename)
{
    if (filename == NULL)
        return WRONG_ARGUMENT;

    log_file = fopen(filename, "w");
    if (log_file == NULL)
        return FILE_ERROR;

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