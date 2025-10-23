#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
    SUCCESS = 0,
    WRONG_FILE_PATH,
    WRONG_ID,
    WRONG_NAME,
    WRONG_GROUP,
    ERROR_ALLOCATE_MEMORY,
    WRONG_NOTES,
    ERROR_VALID,
    ERROR_NOT_FOUND
} StatusCode;

typedef struct Student
{
    unsigned int id;
    char *name;
    char *surname;
    char *group;
    unsigned char *notes;
} Student;

typedef struct Class
{
    Student *someone;
    int count;
    int capacity;
} Class;

StatusCode Create(Student *student);

StatusCode Init_Class(Class *class, int initial_capacity);

StatusCode GetID(const char *str, unsigned int *id);

StatusCode GetSurname(const char *str, char *out);

StatusCode GetGroup(const char *str, char *out);

StatusCode GetNotes(const char *str, unsigned char *notes);

StatusCode Read_File(const char *file_path, Class *class);

void Destroy_Student(Student *student);

void Destroy_Class(Class *class);

void Print(Class class);

StatusCode Search_by(Class *class, const char *out_file);

StatusCode Print_Above_Average(const Class *class, const char *trace_path);

double average_mark(const Student *student);
StatusCode Sort_Class(Class *class, int key);

#endif // STUDENT_H
