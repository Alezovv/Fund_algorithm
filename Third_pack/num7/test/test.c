#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run_test(const char *input, const char *expected_output)
{
    FILE *in = fopen("test_input.txt", "w");
    if (!in)
        return 0;

    fputs(input, in);
    fclose(in);

    int sys_code = system("./bin/main < test_input.txt > test_output.txt");
    if (sys_code != 0)
    {
        fprintf(stderr, "Ошибка: программа завершилась с кодом %d\n", sys_code);
        return 0;
    }

    FILE *out = fopen("test_output.txt", "r");
    if (!out)
        return 0;

    char buffer[2048] = {0};
    size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, out);
    fclose(out);

    if (bytes_read == 0)
    {
        fprintf(stderr, "⚠Нет вывода из программы!\n");
        return 0;
    }

    if (strstr(buffer, expected_output) != NULL)
    {
        printf("Тест пройден: найдено '%s'\n", expected_output);
        return 1;
    }
    else
    {
        printf("Тест не пройден!\n");
        printf("Ожидалось: '%s'\n", expected_output);
        printf("Вывод программы:\n%s\n", buffer);
        return 0;
    }
}

int main(void)
{
    int passed = 0;
    int total = 0;

    printf("Запуск тестов калькулятора...\n\n");

    // Тест 1 простое выражение
    // A = 2 + 3
    // print(A)
    // exit
    // должно быть A = 5
    total++;
    passed += run_test("A = 2 + 3\nprint(A)\nexit\n", "A = 5");

    // Тест 2 использование переменных
    // A = 2 + 3
    // B = A * 4
    // print(B)
    // exit
    // должно быть B = 20
    total++;
    passed += run_test("A = 2 + 3\nB = A * 4\nprint(B)\nexit\n", "B = 20");

    // Тест 3 неопределённая переменная
    // print(Z)
    // должно быть Z не определена
    total++;
    passed += run_test("print(Z)\nexit\n", "Z не определена");

    printf("\nРезультаты тестов: %d / %d пройдено.\n", passed, total);
    return (passed == total) ? 0 : 1;
}
