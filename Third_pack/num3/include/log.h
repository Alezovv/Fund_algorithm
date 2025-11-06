#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include "StatusCode.h"

#define LOG(operation, cur_count, all)                           \
    do                                                           \
    {                                                            \
        fprintf(info.txt, "Operation: %s\n", operation)          \
            fprintf(info.txt, "Current count: %d\n", cur_count); \
        fprintf(info.log, "All count: %d\n", all);               \
    } while (0);

#endif // LOG_H