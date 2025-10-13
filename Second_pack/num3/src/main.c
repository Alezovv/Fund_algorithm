#include "../include/function.h"

int main()
{
    FILE *f = stdout;
    char buf[256];

    overfprintf(f, "Custom base: %Cv\n", 255, 16);
    overfprintf(f, "Base36: %Cv\n", 12345, 36);
    overfprintf(f, "Binary: %CV\n", 255, 2);
    overfprintf(f, "Custom base: %CV\n", 255, 16);
    overfprintf(f, "Base36: %CV\n", 12345, 36);
    overfprintf(f, "Custom base: %to\n", "11111111", 2);
    overfprintf(f, "Base36: %to\n", "9ix", 36);
    overfprintf(f, "Custom base: %TO\n", "11111111", 2);
    overfprintf(f, "Base36: %TO\n", "9IX", 36);
    overfprintf(f, "mi: %mi\n", 12);
    overfprintf(f, "mu: %mu\n", 12);
    overfprintf(f, "md: %md\n", 12.53);
    overfprintf(f, "mf: %mf\n", 12.53f);

    printf("\n--- oversprintf ---\n");

    // oversprintf
    oversprintf(buf, "Custom base: %Cv\n", 255, 16);
    printf("%s", buf);

    oversprintf(buf, "Base36: %Cv\n", 12345, 36);
    printf("%s", buf);

    oversprintf(buf, "Binary: %CV\n", 255, 2);
    printf("%s", buf);

    oversprintf(buf, "Custom base: %CV\n", 255, 16);
    printf("%s", buf);

    oversprintf(buf, "Base36: %CV\n", 12345, 36);
    printf("%s", buf);

    oversprintf(buf, "Custom base: %to\n", "11111111", 2);
    printf("%s", buf);

    oversprintf(buf, "Base36: %to\n", "9ix", 36);
    printf("%s", buf);

    oversprintf(buf, "Custom base: %TO\n", "11111111", 2);
    printf("%s", buf);

    oversprintf(buf, "Base36: %TO\n", "9IX", 36);
    printf("%s", buf);

    oversprintf(buf, "mi: %mi\n", 12);
    printf("%s", buf);

    oversprintf(buf, "mu: %mu\n", 12);
    printf("%s", buf);

    oversprintf(buf, "md: %md\n", 12.53);
    printf("%s", buf);

    oversprintf(buf, "mf: %mf\n", 12.53f);
    printf("%s", buf);

    return 0;
}
