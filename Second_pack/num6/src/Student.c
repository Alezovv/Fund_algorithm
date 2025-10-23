#include "../include/Student.h"
#include "../include/Validation.h"

#define valid              \
    if (status != SUCCESS) \
        return status;

#define print_to_file                                                                                \
    fprintf(fout,                                                                                    \
            "ID: %u\nSurname: %s\nName: %s\nGroup: %s\nNotes: %d %d %d %d %d\nAverage note: %.2f\n", \
            class->someone[i].id,                                                                    \
            class->someone[i].surname,                                                               \
            class->someone[i].name,                                                                  \
            class->someone[i].group,                                                                 \
            class->someone[i].notes[0],                                                              \
            class->someone[i].notes[1],                                                              \
            class->someone[i].notes[2],                                                              \
            class->someone[i].notes[3],                                                              \
            class->someone[i].notes[4],                                                              \
            avg);                                                                                    \
    found = 1;

StatusCode Init_Class(Class *class, int initial_capacity)
{
    if (class == NULL)
        return ERROR_ALLOCATE_MEMORY;
    if (initial_capacity <= 0)
        initial_capacity = 4;
    class->someone = malloc(initial_capacity * sizeof(Student));
    if (!class->someone)
        return ERROR_ALLOCATE_MEMORY;
    class->count = 0;
    class->capacity = initial_capacity;
    return SUCCESS;
}

StatusCode GetID(const char *str, unsigned int *id)
{
    if (str == NULL || id == NULL)
        return WRONG_ID;

    if (*str == '\n' || *str == '\0')
        return WRONG_ID;

    for (const char *ptr = str; *ptr != '\n' && *ptr != '\0'; ptr++)
    {
        if (!isdigit((unsigned char)*ptr))
            return WRONG_ID;
    }

    *id = (unsigned int)strtoul(str, NULL, 10);

    return SUCCESS;
}

StatusCode GetName(const char *str, char *out)
{
    if (str == NULL || *str == '\n' || *str == '\0')
        return WRONG_NAME;

    while (*str != '\n' && *str != '\0')
    {
        if (!isalpha((unsigned char)*str))
            return WRONG_NAME;
        *out++ = *str++;
    }
    *out = '\0';
    return SUCCESS;
}

StatusCode GetGroup(const char *str, char *out)
{
    if (str == NULL || *str == '\n' || *str == '\0')
        return WRONG_GROUP;

    size_t len = strlen(str);
    if (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\0'))
    {
        strncpy(out, str, len - 1);
        out[len - 1] = '\0';
    }
    else
    {
        strcpy(out, str);
    }
    return SUCCESS;
}

StatusCode GetNotes(const char *str, unsigned char *notes)
{
    if (str == NULL || notes == NULL || *str == '\n' || *str == '\0')
        return WRONG_NOTES;

    int i = 0;
    for (const char *ptr = str; *ptr != '\n' && *ptr != '\0' && i < 5; ptr++)
    {
        if (isdigit((unsigned char)*ptr))
        {
            notes[i++] = (unsigned char)(*ptr - '0');
        }
    }

    while (i < 5)
        notes[i++] = 0;

    return SUCCESS;
}

StatusCode Create(Student *student)
{
    if (student == NULL)
        return ERROR_ALLOCATE_MEMORY;

    student->id = 0;
    student->surname = malloc(50);
    student->name = malloc(50);
    student->group = malloc(50);
    student->notes = malloc(5 * sizeof(unsigned char));
    if (!student->surname || !student->name || !student->group || !student->notes)
    {
        Destroy_Student(student);
        return ERROR_ALLOCATE_MEMORY;
    }
    student->surname[0] = '\0';
    student->name[0] = '\0';
    student->group[0] = '\0';
    for (int i = 0; i < 5; i++)
        student->notes[i] = 0;
    return SUCCESS;
}

StatusCode Read_File(const char *file_path, Class *class)
{
    if (file_path == NULL || class == NULL)
        return ERROR_ALLOCATE_MEMORY;

    FILE *file = fopen(file_path, "r");
    if (file == NULL)
        return ERROR_ALLOCATE_MEMORY;

    char line[256];
    int count = 0;
    StatusCode status = SUCCESS;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (class->count >= class->capacity)
        {
            int new_cap = class->capacity * 2;
            Student *tmp = realloc(class->someone, new_cap * sizeof(Student));
            if (!tmp)
            {
                fclose(file);
                return ERROR_ALLOCATE_MEMORY;
            }
            class->someone = tmp;
            class->capacity = new_cap;
        }

        int index = class->count;

        if (count % 5 == 0)
        {
            status = Create(&class->someone[index]);
            if (status != SUCCESS)
            {
                fclose(file);
                return status;
            }
            class->count++;
        }

        index = class->count - 1;

        switch (count % 5)
        {
        case 0:
            status = GetID(line, &class->someone[index].id);
            break;
        case 1:
            status = GetName(line, class->someone[index].name);
            break;
        case 2:
            status = GetName(line, class->someone[index].surname);
            break;
        case 3:
            status = GetGroup(line, class->someone[index].group);
            break;
        case 4:
            status = GetNotes(line, class->someone[index].notes);
            break;
        }

        if (status != SUCCESS)
        {
            fclose(file);
            return status;
        }

        count++;
    }

    fclose(file);
    return SUCCESS;
}

StatusCode Print_Above_Average(const Class *class, const char *trace_path)
{
    if (class == NULL || trace_path == NULL)
        return ERROR_ALLOCATE_MEMORY;
    if (class->count == 0)
        return ERROR_NOT_FOUND;

    FILE *fout = fopen(trace_path, "a");
    if (fout == NULL)
        return ERROR_ALLOCATE_MEMORY;

    double total = 0.0;
    for (int i = 0; i < class->count; i++)
        total += average_mark(&class->someone[i]);
    double group_avg = total / class->count;

    fprintf(fout, "\n--- Students with above-average marks ---\n");
    int found = 0;

    for (int i = 0; i < class->count; i++)
    {
        double avg = average_mark(&class->someone[i]);
        if (avg > group_avg)
        {
            fprintf(fout, "%s %s (%.2f)\n", class->someone[i].surname,
                    class->someone[i].name,
                    avg);
            found = 1;
        }
    }

    if (!found)
        fprintf(fout, "Нет студентов с баллом выше среднего.\n");

    fclose(fout);
    return SUCCESS;
}

StatusCode Search_by(Class *class, const char *out_file)
{
    if (class == NULL || out_file == NULL)
        return ERROR_ALLOCATE_MEMORY;

    FILE *fout = fopen(out_file, "w");
    if (fout == NULL)
        return ERROR_ALLOCATE_MEMORY;

    int found = 0;
    int key = 0;
    if (ValidOptions(&key) != VALID_SUCCESS)
        return ERROR_VALID;

    switch (key)
    {
    case 0:
    {
        printf("Input ID: ");
        unsigned int id = 0;
        if (ValidID(&id) != VALID_SUCCESS)
        {
            fclose(fout);
            return ERROR_VALID;
        }

        for (int i = 0; i < class->count; i++)
        {
            if (class->someone[i].id == id)
            {
                double avg = 0;
                for (int j = 0; j < 5; j++)
                    avg += class->someone[i].notes[j];
                avg /= 5.0;

                print_to_file;
            }
        }
        break;
    }

    case 1:
    {
        printf("Input surname: ");
        char str[128];
        if (ValidSurname(str) != VALID_SUCCESS)
        {
            fclose(fout);
            return ERROR_VALID;
        }

        for (int i = 0; i < class->count; i++)
        {
            if (strcmp(class->someone[i].surname, str) == 0)
            {
                double avg = 0;
                for (int j = 0; j < 5; j++)
                    avg += class->someone[i].notes[j];
                avg /= 5.0;
                print_to_file;
            }
        }
        break;
    }

    case 2:
    {
        printf("Input name: ");
        char str[128];
        if (ValidSurname(str) != VALID_SUCCESS)
        {
            fclose(fout);
            return ERROR_VALID;
        }

        for (int i = 0; i < class->count; i++)
        {
            if (strcmp(class->someone[i].name, str) == 0)
            {
                double avg = 0;
                for (int j = 0; j < 5; j++)
                    avg += class->someone[i].notes[j];
                avg /= 5.0;
                print_to_file;
            }
        }
        break;
    }

    case 3:
    {
        printf("Input group: ");
        char str[128];
        if (ValidGroup(str) != VALID_SUCCESS)
        {
            fclose(fout);
            return ERROR_VALID;
        }

        for (int i = 0; i < class->count; i++)
        {
            if (strcmp(class->someone[i].group, str) == 0)
            {
                double avg = 0;
                for (int j = 0; j < 5; j++)
                    avg += class->someone[i].notes[j];
                avg /= 5.0;
                print_to_file;
            }
        }
        break;
    }

    default:
        fclose(fout);
        return ERROR_VALID;
    }

    fclose(fout);

    if (!found)
    {
        printf("No matches found\n");
        return ERROR_NOT_FOUND;
    }

    printf("Results written to %s\n", out_file);
    return SUCCESS;
}

void Print(Class class)
{
    for (int i = 0; i < class.count; i++)
    {
        Student student = class.someone[i];
        printf("ID = %u\n", student.id);
        printf("Surname = %s\n", student.surname);
        printf("Name = %s\n", student.name);
        printf("Group = %s\n", student.group);
        for (int i = 0; i < 5; i++)
            printf("Note №%d = %d\n", i, student.notes[i]);
    }
}

void Destroy_Student(Student *student)
{
    if (student == NULL)
        return;
    free(student->name);
    free(student->surname);
    free(student->group);
    free(student->notes);

    student->id = 0;
    student->name = NULL;
    student->surname = NULL;
    student->group = NULL;
    student->notes = NULL;
}

void Destroy_Class(Class *class)
{
    if (class == NULL || class->someone == NULL)
        return;

    for (int i = 0; i < class->count; i++)
    {
        Destroy_Student(&class->someone[i]);
    }

    free(class->someone);
    class->someone = NULL;
    class->count = 0;
}


double average_mark(const Student *student)
{
    if (student == NULL || student->notes == NULL)
        return 0.0;

    int sum = 0;
    for (int i = 0; i < 5; i++)
        sum += student->notes[i];

    return sum / 5.0;
}

static int compare_by_id(const void *a, const void *b)
{
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    if (s1->id < s2->id)
        return -1;
    if (s1->id > s2->id)
        return 1;
    return 0;
}

static int compare_by_name(const void *a, const void *b)
{
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    return strcmp(s1->name, s2->name);
}

static int compare_by_surname(const void *a, const void *b)
{
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    return strcmp(s1->surname, s2->surname);
}

static int compare_by_group(const void *a, const void *b)
{
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    return strcmp(s1->group, s2->group);
}

StatusCode Sort_Class(Class *class, int key)
{
    if (class == NULL || class->someone == NULL)
        return ERROR_ALLOCATE_MEMORY;

    switch (key)
    {
    case 0:
        qsort(class->someone, class->count, sizeof(Student), compare_by_id);
        break;
    case 1:
        qsort(class->someone, class->count, sizeof(Student), compare_by_surname);
        break;
    case 2:
        qsort(class->someone, class->count, sizeof(Student), compare_by_name);
        break;
    case 3:
        qsort(class->someone, class->count, sizeof(Student), compare_by_group);
        break;
    default:
        return ERROR_VALID;
    }

    return SUCCESS;
}