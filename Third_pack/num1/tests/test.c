#include <string.h>
#include "../include/ToBase.h"

void test_to_base_2r()
{
    struct
    {
        unsigned int number;
        int n;
        const char *expected;
    } tests[] = {
        {0, 1, "0"},
        {1, 1, "1"},
        {2, 1, "10"},
        {7, 2, "13"},
        {255, 3, "377"},
        {255, 4, "FF"},
        {255, 5, "7V"},
        {1023, 5, "VV"}};

    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < num_tests; i++)
    {
        char *res = to_base_2r(tests[i].number, tests[i].n);
        if (res == NULL)
        {
            printf("Ошибка: NULL при числе %u и n=%d\n", tests[i].number, tests[i].n);
            continue;
        }

        if (strcmp(res, tests[i].expected) == 0)
        {
            printf("Passed %u (2^%d) = %s\n", tests[i].number, tests[i].n, res);
            passed++;
        }
        else
        {
            printf("Fail %u (2^%d): ожидалось %s, получено %s\n",
                   tests[i].number, tests[i].n, tests[i].expected, res);
        }

        free(res);
    }

    printf("Результат: %d/%d тестов успешно.\n\n", passed, num_tests);
}

int main()
{
    test_to_base_2r();
    return 0;
}
