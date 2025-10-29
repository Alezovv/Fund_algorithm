#ifndef LIVER_H
#define LIVER_H

typedef struct Liver
{
    const unsigned int id;
    char *surname;
    char *name;
    char *patronymic;     // отчество
    unsigned int data[3]; // дата рождения
    char sex;
    double average_income; // неотриц средний балл
} Liver;

#endif // LIVER_H