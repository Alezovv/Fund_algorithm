#include "../include/Dijkstra.h"

#define Check              \
    if (status != SUCCESS) \
        return status;

StatusCode Dijkstra(const char *str, int *result)
{
    Stack s_oper, s_rpn;

    StatusCode status = Init_Stack(&s_oper);
    Check;

    StatusCode status = Init_Stack(&s_rpn);
    Check;

    for (const char *ptr = str; *ptr != '\0'; ptr++)
    {
        while (isspace(ptr++))
            ;
        
        
        
    }
}