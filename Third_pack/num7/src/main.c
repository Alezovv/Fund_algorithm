#include "../include/Stack.h"
#include "../include/Dijkstra.h"
#include "../include/StatusCode.h"
#include "../include/Calculate.h"
#include "../include/Logging.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    print_usage();
    char str[256];
    Stack s;
    int is_print = 0;
    char descr[100];
    int count = 1;

    if (Init_Stack(&s) != SUCCESS)
    {
        LOG_ERROR("Ошибка инициализации стека!");
        return 1;
    }

    if (Init_Logger("info.log") != SUCCESS)
    {
        LOG_ERROR("Ошибка инициализации логов!");
        Stack_Destroy(&s);
        return 1;
    }

    LOG_DESCRIPTION("Начало обработки");

    char *mem[26] = {NULL};

    while (1)
    {
        LOG_COUNT(count++);
        printf("> ");
        if (fgets(str, sizeof(str), stdin) == NULL)
        {
            LOG_ERROR("Ошибка при вводе!");
            break;
        }

        LOG_STRING(str);

        str[strcspn(str, "\n")] = '\0';

        if (strlen(str) == 0)
            continue;

        if (strcmp(str, "exit") == 0)
            break;

        StatusCode status = Validate_Expression(str, &is_print);
        if (status != SUCCESS)
        {
            LOG_ERROR(Status_Handle(status));
            LOG_ARRAY(mem);
            continue;
        }

        // print
        if (is_print)
        {
            char var = '\0';
            if (sscanf(str, " print ( %c ) ", &var) != 1)
            {
                LOG_ARRAY(mem);
                LOG_ERROR("Неверный синтаксис print (пример: print(A))");
                continue;
            }

            if (!(var >= 'A' && var <= 'Z'))
            {
                LOG_ARRAY(mem);
                LOG_ERROR("Некорректное имя переменной для print");
                continue;
            }

            if (mem[var - 'A'] != NULL)
            {
                printf("%c = %s\n", var, mem[var - 'A']);
                snprintf(descr, sizeof(descr), "Print %c", var);
            }
            else
            {
                printf("%c не определена\n", var);
                LOG_ERROR("Переменная не определена");
                snprintf(descr, sizeof(descr), "Print %c (undefined)", var);
            }
        }
        // выражение
        else
        {
            char *equals_pos = strchr(str, '=');
            if (equals_pos == NULL)
            {
                LOG_ARRAY(mem);
                LOG_ERROR("В выражении отсутствует '='");
                continue;
            }

            char target_var = '\0';
            for (int i = 0; i < (equals_pos - str); i++)
            {
                if (!isspace((unsigned char)str[i]))
                {
                    target_var = str[i];
                    break;
                }
            }

            if (!(target_var >= 'A' && target_var <= 'Z'))
            {
                LOG_ARRAY(mem);
                LOG_ERROR("Некорректное имя переменной слева от '='");
                continue;
            }

            char *expression = equals_pos + 1;
            while (isspace((unsigned char)*expression))
                expression++;

            Stack_Destroy(&s);
            if (Init_Stack(&s) != SUCCESS)
            {
                LOG_ARRAY(mem);
                LOG_ERROR("Ошибка переинициализации стека");
                continue;
            }

            char substituted[256];
            Substitute_Variables(expression, substituted, mem);
            status = Dijkstra(substituted, &s);
            if (status != SUCCESS)
            {
                LOG_ARRAY(mem);
                LOG_ERROR(Status_Handle(status));
                continue;
            }

            int result = 0;
            status = Rpn_Calculate(&s, &result);
            if (status != SUCCESS)
            {
                LOG_ARRAY(mem);
                LOG_ERROR(Status_Handle(status));
                continue;
            }

            char result_str[20];
            snprintf(result_str, sizeof(result_str), "%d", result);

            free(mem[target_var - 'A']);

            mem[target_var - 'A'] = malloc(strlen(result_str) + 1);
            if (mem[target_var - 'A'] == NULL)
            {
                LOG_ARRAY(mem);
                LOG_ERROR("Ошибка выделения памяти");
                continue;
            }

            strcpy(mem[target_var - 'A'], result_str);
            snprintf(descr, sizeof(descr), "Assign %c = %d", target_var, result);
        }

        LOG_ARRAY(mem);
        LOG_DESCRIPTION(descr);
    }

    Stack_Destroy(&s);
    for (int i = 0; i < 26; i++)
    {
        free(mem[i]);
        mem[i] = NULL;
    }

    Close_Logger();
    return 0;
}
