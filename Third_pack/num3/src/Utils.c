#include "../include/Utils.h"

void print_usage()
{
    printf("Usage: <program name> <path_to_file>\n");
    printf("Example: main file.txt\n");
}

void select_options()
{
    printf("Select options\n");
    printf("0 - Search person\n");
    printf("1 - Change person\n");
    printf("2 - Delete person\n");
    printf("3 - Add person\n");
    printf("4 - Write to file\n");
    printf("5 - Discard last n / 2 modification\n");
}

StatusCode valid_path(const char *path)
{
    FILE *file = fopen(path, "w");
    if (file == NULL)
        return FILE_ERROR;

    fclose(file);
    return SUCCESS;
}

StatusCode scan_file(const char *path, list *lst)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
        return FILE_ERROR;

    if (!lst)
    {
        fclose(file);
        return LIST_NOT_INITIALIZED;
    }

    Liver *l = (Liver *)malloc(sizeof(Liver));
    while (fscanf(file, "%u %49s %49s %49s %u %u %u %c %.2f",
                  l->id, l->surname, l->name, l->patronymic, l->data[0],
                  l->data[1], l->data[2], l->sex, l->average_income) == 1)
    {
        push_back_list(lst, l);
    }

    fclose(file);
    return SUCCESS;
}

StatusCode write_to_file(const char *path, list *lst)
{
    FILE *file = fopen(path, "w");
    if (file == NULL)
        return FILE_ERROR;

    if (!lst || lst->size == 0)
    {
        fclose(file);
        return LIST_NOT_INITIALIZED;
    }

    size_t size = lst->size;
    for (size_t i = 0; i < size; i++)
    {
        Liver l = get_at_list(lst, i);
        fprintf(file, "id: %u\n", l.id);
        fprintf(file, "surname: %s\n", l.surname);
        fprintf(file, "name: %s\n", l.name);
        fprintf(file, "patronymic: %s\n", l.patronymic);
        fprintf(file, "birthday: %u.%u.%u\n", l.data[0], l.data[1], l.data[2]);
        fprintf(file, "sex: %c\n", l.sex);
        fprintf(file, "average_income: %.2f\n", l.average_income);
        fprintf(file, "----------------------\n");
    }

    fclose(file);

    return SUCCESS;
}

StatusCode Search_By(list *lst, size_t attr)
{
    switch (attr)
    {
    case 0:
    {
        printf("Введите id: ");
        int tmp = 0;
        if (scanf("%d", &tmp) != 1)
            return SCAN_ERROR;
        Liver liv;
        for (size_t i = 0; i < lst->size; i++)
        {
            liv = get_at_list(lst, i);
        }
    }
    }
}