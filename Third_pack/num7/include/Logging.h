#ifndef LOGGING_H
#define LOGGING_H

#include "StatusCode.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LET_COUNT 26

StatusCode Init_Logger(const char *filename);
void Close_Logger();
const char *Status_Handle(StatusCode status);
void print_usage();

#define LOG_ARRAY(arr)                                               \
    do                                                               \
    {                                                                \
        if (log_file != NULL)                                        \
        {                                                            \
            int empty = 1;                                           \
            fprintf(log_file, "DATA: \n");                           \
            for (int i = 0; i < LET_COUNT; i++)                      \
            {                                                        \
                if (arr[i] != NULL)                                  \
                {                                                    \
                    fprintf(log_file, "%c = %s\n", 'A' + i, arr[i]); \
                    empty = 0;                                       \
                }                                                    \
            }                                                        \
            if (empty)                                               \
                fprintf(log_file, "No data\n");                      \
                                                                     \
            fprintf(log_file, "\n");                                 \
            fflush(log_file);                                        \
        }                                                            \
    } while (0)

#define LOG_STRING(str)                             \
    do                                              \
    {                                               \
        if (log_file != NULL)                       \
        {                                           \
            fprintf(log_file, "STRING: %s\n", str); \
            fflush(log_file);                       \
        }                                           \
    } while (0)

#define LOG_ERROR(msg)                             \
    do                                             \
    {                                              \
        if (log_file != NULL)                      \
        {                                          \
            fprintf(log_file, "ERROR: %s\n", msg); \
            fflush(log_file);                      \
        }                                          \
    } while (0)

#define LOG_DESCRIPTION(value)                               \
    do                                                       \
    {                                                        \
        if (log_file != NULL)                                \
        {                                                    \
            fprintf(log_file, "DESCRIPTION: %s\n\n", value); \
            fflush(log_file);                                \
        }                                                    \
    } while (0)

#define LOG_COUNT(count)                                          \
    do                                                            \
    {                                                             \
        fprintf(log_file, "=======================");             \
        fprintf(log_file, "Current program counter: %d ", count); \
        fprintf(log_file, "=======================\n");           \
        fflush(log_file);                                         \
    } while (0);

extern FILE *log_file;

#endif // LOGGING_H