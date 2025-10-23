#include "../include/function.h"

int main(void)
{
    char input_path[256], output_path[256];

    printf("Enter input file path: ");
    if (!fgets(input_path, sizeof(input_path), stdin))
    {
        fprintf(stderr, "Error reading input path\n");
        return 1;
    }
    input_path[strcspn(input_path, "\n")] = '\0';

    printf("Enter output file path: ");
    if (!fgets(output_path, sizeof(output_path), stdin))
    {
        fprintf(stderr, "Error reading output path\n");
        return 1;
    }
    output_path[strcspn(output_path, "\n")] = '\0';

    FILE *fin = fopen(input_path, "r");
    if (!fin)
    {
        perror("Error opening input file");
        return 1;
    }

    FILE *fout = fopen(output_path, "w");
    if (!fout)
    {
        perror("Error opening output file");
        fclose(fin);
        return 1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fin))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        process_line(fout, buffer);
    }

    fclose(fin);
    fclose(fout);

    printf("Text formatted and written to %s\n", output_path);
    return 0;
}
