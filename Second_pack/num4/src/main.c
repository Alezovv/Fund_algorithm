#include "../include/function.h"

int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (!f)
    {
        perror("input.txt");
        return 1;
    }

    int rom1, rom2;
    unsigned int z1, z2;

    overfscanf(f, "%Ro %Ro %Zr %Zr", &rom1, &rom2, &z1, &z2);

    printf("Roman1 = %d\nRoman2 = %d\nZeck1 = %u\nZeck2 = %u\n",
           rom1, rom2, z1, z2);

    int n1, n2, n3;
    overfscanf(f, "%Cv %Cv %CV", &n1, 2, &n2, 16, &n3, 16);
    fclose(f);

    printf("n1 = %d\nn2 = %d\nn3 = %d\n", n1, n2, n3);

    const char *input = "xiv 10101 1a 2B";
    int r, cv, CV;
    unsigned int z;

    int n = oversscanf(input, "%Ro %Zr %Cv %CV", &r, &z, &cv, 16, &CV, 16);
    printf("n=%d\nroman=%d\nzeck=%u\ncv=%d\nCV=%d\n", n, r, z, cv, CV);

    return 0;
}