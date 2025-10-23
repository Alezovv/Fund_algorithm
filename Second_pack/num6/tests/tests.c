#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/Student.h"

Student create_test_student(unsigned int id, const char *name, const char *surname, const char *group, unsigned char notes[5])
{
    Student s;
    s.id = id;
    s.name = malloc(50);
    s.surname = malloc(50);
    s.group = malloc(50);
    s.notes = malloc(5 * sizeof(unsigned char));
    assert(s.name && s.surname && s.group && s.notes);

    strcpy(s.name, name);
    strcpy(s.surname, surname);
    strcpy(s.group, group);
    for (int i = 0; i < 5; i++)
        s.notes[i] = notes[i];
    return s;
}

int main(void)
{
    printf("=== Running tests ===\n");

    Class cls;
    StatusCode status = Init_Class(&cls, 2);
    assert(status == SUCCESS);
    assert(cls.count == 0);
    assert(cls.capacity == 2);
    printf("Init_Class test passed.\n");

    unsigned char notes1[5] = {5, 4, 3, 5, 4};
    Student s1 = create_test_student(1, "John", "Doe", "CS101", notes1);
    assert(average_mark(&s1) == 4.2);
    printf("Create Student & average_mark test passed.\n");

    unsigned char notes2[5] = {4, 5, 5, 4, 3};
    Student s2 = create_test_student(2, "Jane", "Smith", "CS101", notes2);
    assert(average_mark(&s2) == 4.2);

    cls.someone[cls.count++] = s1;
    cls.someone[cls.count++] = s2;

    status = Sort_Class(&cls, 1); // 1 = surname
    assert(status == SUCCESS);
    assert(strcmp(cls.someone[0].surname, "Doe") == 0);
    assert(strcmp(cls.someone[1].surname, "Smith") == 0);
    printf("Sort_Class by surname test passed.\n");

    status = Sort_Class(&cls, 0); // 0 = id
    assert(status == SUCCESS);
    assert(strcmp(cls.someone[0].surname, "Doe") == 0);
    assert(strcmp(cls.someone[1].surname, "Smith") == 0);
    printf("Sort_Class by id test passed.\n");

    Destroy_Student(&s1);
    Destroy_Student(&s2);
    free(cls.someone);

    printf("All tests completed successfully.\n");
    return 0;
}
