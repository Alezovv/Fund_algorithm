#include <stdio.h>
#include <stdlib.h>

#define memory_size 26

int main()
{
    int memory[memory_size + 1] = {NULL};
    char *str = ' ';
    while (*str != EOF)
    {
        if(scanf("%s", str) != 1)
            return 1;
        
        
    }
    return 0;
}
