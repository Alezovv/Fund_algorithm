#ifndef LIVER_H
#define LIVER_H


typedef struct Liver
{
    unsigned int id;
    char *surname;
    char *name;
    char *patronymic;     // отчество
    unsigned int data[3]; // дата рождения
    char sex;
    double average_income; // неотриц средний балл
} Liver;

int Liv_Cmp(Liver *l1, Liver *l2);

#endif // LIVER_H
