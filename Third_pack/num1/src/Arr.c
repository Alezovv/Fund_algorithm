#include "../include/Arr.h"


char **init_array()
{
    char **array = (char **)malloc(r * sizeof(char *));
    if (array == NULL)
        return NULL;

    for (int i = 0; i < r; i++)
        array[i] = NULL;

    return array;
}

void free_array(char **array)
{
    if (array == NULL)
        return;

    for (int i = 0; i < r; i++)
    {
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
}

void print_array(int number, char **array)
{
    for (int i = 0; i < r; i++)
        printf("Число %d в 2^%d с.с  = %s\n", number, i + 1, array[i]);
}