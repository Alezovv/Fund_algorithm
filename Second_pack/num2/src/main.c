#include "../include/function.h"

int main(void)
{
    printf("Running tests...\n\n");

    const char mem_data[] = {'A', 'B', 'C', 'D', 'E', 0};
    char *ptr1 = memchr(mem_data, 'C', 6);
    assert(ptr1 != NULL && *ptr1 == 'C');
    printf("memchr: PASSED\n");

    char a[] = "abcde";
    char b[] = "abCde";
    assert(memcmp(a, b, 3) == 0);
    assert(memcmp(a, b, 4) != 0);
    printf("memcmp: PASSED\n");

    char dest[6] = {0};
    memcpy(dest, "hello", 5);
    assert(memcmp(dest, "hello", 5) == 0);
    printf("memcpy: PASSED\n");

    char buf[5];
    memset(buf, 'x', 5);
    for (int i = 0; i < 5; i++)
        assert(buf[i] == 'x');
    printf("memset: PASSED\n");

    char s1[20] = "Hi ";
    char s2[] = "World";
    strncat(s1, s2, 3);
    assert(strcmp(s1, "Hi Wor") == 0);
    printf("strncat: PASSED\n");

    char *ptr2 = strchr("abcdef", 'd');
    assert(ptr2 != NULL && *ptr2 == 'd');
    printf("strchr: PASSED\n");

    assert(strncmp("abcdef", "abcxyz", 3) == 0);
    assert(strncmp("abcdef", "abcxyz", 4) != 0);
    printf("strncmp: PASSED\n");

    char s3[10] = {0};
    strncpy(s3, "test", 6);
    assert(strcmp(s3, "test") == 0);
    printf("strncpy: PASSED\n");

    size_t len = strcspn("abcdef", "de");
    assert(len == 3);
    printf("strcspn: PASSED\n");

    char *msg = strerror(2);
    printf("strerror: %s\n", msg);

    assert(strlen("hello") == 5);
    printf("strlen: PASSED\n");

    char *ptr3 = strpbrk("abcdef", "xzcd");
    assert(ptr3 != NULL && *ptr3 == 'c');
    printf("strpbrk: PASSED\n");

    char *ptr4 = strrchr("abccdecc", 'c');
    assert(ptr4 != NULL && *ptr4 == 'c' && ptr4 == &("abccdecc"[7]));
    printf("strrchr: PASSED\n");

    char *ptr5 = strstr("hello world", "lo wo");
    assert(ptr5 != NULL && ptr5[0] == 'l');
    printf("strstr: PASSED\n");

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