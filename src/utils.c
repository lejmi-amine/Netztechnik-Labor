#include <ctype.h>
#include <string.h>
#include "utils.h"

void trim(char *str)
{
    int i, start = 0, end = strlen(str) - 1;

    while (isspace((unsigned char)str[start])) start++;
    while (end >= start && isspace((unsigned char)str[end])) end--;

    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
}

int isValid(const char *str)
{
    if (!isalpha(str[0])) return 0;

    for (int i = 1; str[i] != '\0'; i++)
        if (!isalnum((unsigned char)str[i])) return 0;

    return 1;
}

int checkline(const char *line)
{
    const char *p = line;

    while (*p && isspace((unsigned char)*p)) p++;

    if (*p == '\0') return 1;   
    if (p[0] == '/' && p[1] == '/') return 1;

    return 0;
}
