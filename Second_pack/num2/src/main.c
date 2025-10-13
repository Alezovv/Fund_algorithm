#include "../include/function.h"

int main(void)
{
    printf("Running tests...\n\n");

    // ==== memchr ====
    const char mem_data[] = {'A', 'B', 'C', 'D', 'E', 0};
    char *ptr1 = memchr(mem_data, 'C', 6);
    assert(ptr1 != NULL && *ptr1 == 'C');
    printf("memchr: PASSED\n");

    // ==== memcmp ====
    char a[] = "abcde";
    char b[] = "abCde";
    assert(memcmp(a, b, 3) == 0); // первые 3 символа равны
    assert(memcmp(a, b, 4) != 0);
    printf("memcmp: PASSED\n");

    // ==== memcpy ====
    char dest[6] = {0};
    memcpy(dest, "hello", 5);
    assert(memcmp(dest, "hello", 5) == 0);
    printf("memcpy: PASSED\n");

    // ==== memset ====
    char buf[5];
    memset(buf, 'x', 5);
    for (int i = 0; i < 5; i++)
        assert(buf[i] == 'x');
    printf("memset: PASSED\n");

    // ==== strncat ====
    char s1[20] = "Hi ";
    char s2[] = "World";
    strncat(s1, s2, 3);
    assert(strcmp(s1, "Hi Wor") == 0);
    printf("strncat: PASSED\n");

    // ==== strchr ====
    char *ptr2 = strchr("abcdef", 'd');
    assert(ptr2 != NULL && *ptr2 == 'd');
    printf("strchr: PASSED\n");

    // ==== strncmp ====
    assert(strncmp("abcdef", "abcxyz", 3) == 0);
    assert(strncmp("abcdef", "abcxyz", 4) != 0);
    printf("strncmp: PASSED\n");

    // ==== strncpy ====
    char s3[10] = {0};
    strncpy(s3, "test", 6);
    assert(strcmp(s3, "test") == 0);
    printf("strncpy: PASSED\n");

    // ==== strcspn ====
    size_t len = strcspn("abcdef", "de");
    assert(len == 3);
    printf("strcspn: PASSED\n");

    // ==== strerror ====
    char *msg = strerror(2); // должно вернуть сообщение об ошибке
    printf("strerror: %s\n", msg);

    // ==== strlen ====
    assert(strlen("hello") == 5);
    printf("strlen: PASSED\n");

    // ==== strpbrk ====
    char *ptr3 = strpbrk("abcdef", "xzcd");
    assert(ptr3 != NULL && *ptr3 == 'c');
    printf("strpbrk: PASSED\n");

    // ==== strrchr ====
    char *ptr4 = strrchr("abccdecc", 'c');
    assert(ptr4 != NULL && *ptr4 == 'c' && ptr4 == &("abccdecc"[7]));
    printf("strrchr: PASSED\n");

    // ==== strstr ====
    char *ptr5 = strstr("hello world", "lo wo");
    assert(ptr5 != NULL && ptr5[0] == 'l');
    printf("strstr: PASSED\n");

    // ==== strtok ====
    char str6[] = "one,two,three";
    char *tok = strtok(str6, ",");
    assert(tok != NULL && strcmp(tok, "one") == 0);
    tok = strtok(NULL, ",");
    assert(tok != NULL && strcmp(tok, "two") == 0);
    tok = strtok(NULL, ",");
    assert(tok != NULL && strcmp(tok, "three") == 0);
    tok = strtok(NULL, ",");
    assert(tok == NULL);
    printf("strtok: PASSED\n");

    printf("\nAll tests PASSED!\n");

    return 0;
}