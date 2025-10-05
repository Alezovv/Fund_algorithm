#include "../include/validations.h"
#include "../include/flags.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_validation()
{
    printf("Testing validation...\n");

    // Тест валидации аргументов
    char *valid_args[] = {"program", "-d", "input.txt"};
    char *invalid_args[] = {"program", "-x", "input.txt"};
    char *few_args[] = {"program", "-d"};

    assert(validate_arguments(3, valid_args) == VALIDATION_SUCCESS);
    assert(validate_arguments(3, invalid_args) == VALIDATION_INVALID_FLAG);
    assert(validate_arguments(2, few_args) == VALIDATION_INVALID_ARGC);

    printf("Validation tests passed\n\n");
}

void test_flag_d()
{
    printf("Testing flag -d...\n");

    // Создаем тестовый файл
    FILE *test_file = fopen("test_d.txt", "w");
    fprintf(test_file, "Hello123 World456!");
    fclose(test_file);

    // Тестируем флаг -d
    FILE *input = fopen("test_d.txt", "r");
    FILE *output = fopen("test_d_out.txt", "w");

    flag_d(input, output);

    fclose(input);
    fclose(output);

    // Проверяем результат
    FILE *result = fopen("test_d_out.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), result);
    fclose(result);

    assert(strcmp(buffer, "Hello World!") == 0);

    // Убираем временные файлы
    remove("test_d.txt");
    remove("test_d_out.txt");

    printf("Flag -d tests passed\n\n");
}

void test_flag_i()
{
    printf("Testing flag -i...\n");

    FILE *test_file = fopen("test_i.txt", "w");
    fprintf(test_file, "Hello123 World!\nTest456");
    fclose(test_file);

    FILE *input = fopen("test_i.txt", "r");
    FILE *output = fopen("test_i_out.txt", "w");

    flag_i(input, output);

    fclose(input);
    fclose(output);

    // Проверяем результат
    FILE *result = fopen("test_i_out.txt", "r");
    char line1[10], line2[10];
    fgets(line1, sizeof(line1), result);
    fgets(line2, sizeof(line2), result);
    fclose(result);

    assert(atoi(line1) == 10); // "Hello World!" - 10 букв
    assert(atoi(line2) == 4);  // "Test" - 4 буквы

    remove("test_i.txt");
    remove("test_i_out.txt");

    printf("Flag -i tests passed\n\n");
}

void test_flag_s()
{
    printf("Testing flag -s...\n");

    FILE *test_file = fopen("test_s.txt", "w");
    fprintf(test_file, "Hello, World!\nTest @#$");
    fclose(test_file);

    FILE *input = fopen("test_s.txt", "r");
    FILE *output = fopen("test_s_out.txt", "w");

    flag_s(input, output);

    fclose(input);
    fclose(output);

    FILE *result = fopen("test_s_out.txt", "r");
    char line1[10], line2[10];
    fgets(line1, sizeof(line1), result);
    fgets(line2, sizeof(line2), result);
    fclose(result);

    assert(atoi(line1) == 2); // ",!" - 2 символа
    assert(atoi(line2) == 3); // " @#$" - 3 символа (пробел не считается)

    remove("test_s.txt");
    remove("test_s_out.txt");

    printf("Flag -s tests passed\n\n");
}

void test_flag_a()
{
    printf("Testing flag -a...\n");

    FILE *test_file = fopen("test_a.txt", "w");
    fprintf(test_file, "AB12");
    fclose(test_file);

    FILE *input = fopen("test_a.txt", "r");
    FILE *output = fopen("test_a_out.txt", "w");

    flag_a(input, output);

    fclose(input);
    fclose(output);

    FILE *result = fopen("test_a_out.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), result);
    fclose(result);

    // 'A'=0x41, 'B'=0x42, '1'='1', '2'='2'
    assert(strstr(buffer, "4142") != NULL); // Проверяем наличие hex кодов
    assert(strstr(buffer, "12") != NULL);   // Проверяем что цифры остались

    remove("test_a.txt");
    remove("test_a_out.txt");

    printf("Flag -a tests passed\n\n");
}

void test_file_validation()
{
    printf("Testing file validation...\n");

    // Создаем временный файл для теста
    FILE *tmp = fopen("test_valid.txt", "w");
    fprintf(tmp, "test content");
    fclose(tmp);

    assert(validate_file("test_valid.txt") == VALIDATION_SUCCESS);
    assert(validate_file("nonexistent.txt") == VALIDATION_INVALID_FILE);
    assert(validate_file("") == VALIDATION_INVALID_FILE);

    remove("test_valid.txt");

    printf("File validation tests passed\n\n");
}

void run_all_tests()
{
    printf("Running file processor tests...\n\n");

    test_validation();
    test_file_validation();
    test_flag_d();
    test_flag_i();
    test_flag_s();
    test_flag_a();

    printf("\nAll tests passed!\n");
}

int main()
{
    run_all_tests();
    return 0;
}