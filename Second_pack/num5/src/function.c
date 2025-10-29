#include "../include/function.h"

void justify_line(const char *line, char *out)
{
#define MAX_WORDS 128
    char words[MAX_WORDS][LINE_WIDTH];
    int word_lengths[MAX_WORDS];
    int n_words = 0;

    int i = 0, j = 0;
    int len = strlen(line);

    // Разделение строки на слова
    while (i < len)
    {
        while (i < len && isspace((unsigned char)line[i]))
            i++;
        if (i >= len)
            break;

        j = 0;
        while (i < len && !isspace((unsigned char)line[i]) && j < LINE_WIDTH - 1)
            words[n_words][j++] = line[i++];

        words[n_words][j] = '\0';
        word_lengths[n_words] = j;
        n_words++;
        if (n_words >= MAX_WORDS)
            break;
    }

    if (n_words == 0)
    {
        strcpy(out, "");
        return;
    }

    int total_chars = 0;
    for (i = 0; i < n_words; i++)
        total_chars += word_lengths[i];

    int total_spaces = LINE_WIDTH - total_chars;
    if (total_spaces < 0)
        total_spaces = 0;

    int space_between = n_words > 1 ? total_spaces / (n_words - 1) : total_spaces;
    int extra_spaces = n_words > 1 ? total_spaces % (n_words - 1) : 0;

    out[0] = '\0';
    for (i = 0; i < n_words; i++)
    {
        strncat(out, words[i], LINE_WIDTH - strlen(out) - 1);
        if (i < n_words - 1)
        {
            int s = space_between + (extra_spaces-- > 0 ? 1 : 0);
            for (j = 0; j < s && strlen(out) < LINE_WIDTH - 1; j++)
                strncat(out, " ", LINE_WIDTH - strlen(out) - 1);
        }
    }
}

void process_line(FILE *fout, char *buffer)
{
    size_t len = strlen(buffer);
    size_t start = 0;

    while (len - start > LINE_WIDTH)
    {
        size_t end = start + LINE_WIDTH;

        // ищем ближайший пробел для переноса
        while (end > start && end <= len && !isspace((unsigned char)buffer[end - 1]))
            end--;

        if (end == start)
            end = start + LINE_WIDTH;

        char line[LINE_WIDTH + 1];
        memset(line, 0, sizeof(line));
        memcpy(line, buffer + start, end - start);
        line[end - start] = '\0';

        char justified[LINE_WIDTH + 1];
        memset(justified, 0, sizeof(justified));
        justify_line(line, justified);

        fprintf(fout, "%s\n", justified);

        start = end;
        while (isspace((unsigned char)buffer[start]))
            start++;
    }

    if (start < len)
    {
        char last_line[LINE_WIDTH + 1];
        memset(last_line, 0, sizeof(last_line));
        strncpy(last_line, buffer + start, LINE_WIDTH);
        fprintf(fout, "%s\n", last_line);
    }
}
