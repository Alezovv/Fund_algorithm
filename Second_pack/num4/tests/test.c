#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/function.h"

int main(void)
{
    printf("=== Running function tests ===\n");

    FILE *f = fopen("tests/test_input.txt", "w+");
    assert(f != NULL);

    fprintf(f, "X IV 1011 11\n");
    fprintf(f, "1a 2B 1c\n");
    rewind(f);

    int rom1 = 0, rom2 = 0;
    unsigned int z1 = 0, z2 = 0;
    int n1 = 0, n2 = 0, n3 = 0;

    int ret = overfscanf(f, "%Ro %Ro %Zr %Zr", &rom1, &rom2, &z1, &z2);
    printf("overfscanf returned %d\n", ret);
    printf("Roman1 = %d, Roman2 = %d, Zeck1 = %u, Zeck2 = %u\n", rom1, rom2, z1, z2);

    assert(ret == 4);

    ret = overfscanf(f, "%Cv %Cv %CV", &n1, 2, &n2, 16, &n3, 16);
    printf("Cv/CV values: n1=%d, n2=%d, n3=%d\n", n1, n2, n3);
    assert(ret == 3);

    fclose(f);

    const char *input = "xiv 1011 1a 2B";
    int r = 0, cv = 0, CV = 0;
    unsigned int z = 0;

    int n = oversscanf(input, "%Ro %Zr %Cv %CV", &r, &z, &cv, 16, &CV, 16);
    printf("oversscanf returned %d\n", n);
    printf("roman=%d, zeck=%u, cv=%d, CV=%d\n", r, z, cv, CV);

    assert(n == 4);
    assert(r == 14);  // xiv = 14
    assert(z == 4);   // 1011 по твоей функции -> 4
    assert(cv == 26); // 1a -> 26 в base16
    assert(CV == 43); // 2B -> 43 в base16

    printf("All function tests passed successfully.\n");

    return 0;
}
