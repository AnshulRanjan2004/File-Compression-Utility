//Implementation of horspool algorithm

#include <stdio.h>
#include <string.h>

#define MAX 100

int shift_table[MAX];

void shift_table_init(char *pattern)
{
    int i, j, m;

    m = strlen(pattern);

    for (i = 0; i < MAX; i++)
        shift_table[i] = m;

    for (j = 0; j < m - 1; j++)
        shift_table[pattern[j]] = m - 1 - j;
}

int horspool(char *text, char *pattern)
{
    int i, k, m, n;
    n = strlen(text);
    m = strlen(pattern);
    i = m - 1;

    while (i < n)
    {
        k = 0;
        while ((k < m) && (pattern[m - 1 - k] == text[i - k]))
            k++;
        if (k == m)
            return (i - m + 1);
        else
            i += shift_table[text[i]];
    }
    return -1;
}

int main()
{
    char text[MAX], pattern[MAX];
    int pos;

    printf("Enter the text in which pattern is to be searched:  ");
    gets(text);
    printf("Enter the pattern to be searched:  ");
    gets(pattern);

    shift_table_init(pattern);
    pos = horspool(text, pattern);

    if (pos >= 0)
        printf("The desired pattern was found starting from position %d", pos);
    else
        printf("The pattern was not found in the given text");

    return 0;
}
