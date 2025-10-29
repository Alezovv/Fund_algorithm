#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/Stack.h"
#include "../include/Check_Brackets.h"

void test_check_brackets()
{
    Stack s;
    StackInit(&s);
    StatusCode status;

    // Корректные выражения
    const char *good[] = {"()", "([]{})", "({[<>]})", "", "<{[()]}>"};
    for (size_t i = 0; i < sizeof(good) / sizeof(good[0]); i++)
    {
        status = check_brackets(&s, good[i]);
        assert(status == STATUS_SUCCESS);
    }

    // Некорректные выражения
    const char *bad[] = {"(", "[", "{", "(]", "{)", "[}", "((({[[[<<<", "))}]]>>>"};
    for (size_t i = 0; i < sizeof(bad) / sizeof(bad[0]); i++)
    {
        status = check_brackets(&s, bad[i]);
        assert(status != STATUS_SUCCESS);
    }

    DeleteStack(&s);
}

int main()
{

    printf("Тестируем проверку скобок...\n");
    test_check_brackets();

    printf("Все тесты успешно пройдены!\n");
    return 0;
}
