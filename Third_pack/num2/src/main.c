#include <stdio.h>
#include "../include/Vector.h"

DEFINE_VECTOR(int, IntVector)
IMPLEMENT_VECTOR(int, IntVector)

int main(void)
{
    IntVector v = create_IntVector(4, NULL, NULL);

    for (int i = 0; i < 10; i++)
        push_back_IntVector(&v, i * 10);

    printf("Элементы вектора:\n");
    for (size_t i = 0; i < v.size; i++)
        printf("[%lu] = %d\n", i, get_at_IntVector(&v, i));

    delete_at_IntVector(&v, 3);

    printf("После удаления (3 элемент):\n");
    for (size_t i = 0; i < v.size; i++)
        printf("[%lu] = %d\n", i, get_at_IntVector(&v, i));

    printf("Скопированный:\n");
    IntVector *copy = copy_IntVector_new(&v);
    for (size_t i = 0; i < copy->size; i++)
        printf("[%lu] = %d\n", i, get_at_IntVector(copy, i));

    delete_IntVector(&v);
    delete_IntVector(copy);

    return 0;
}
