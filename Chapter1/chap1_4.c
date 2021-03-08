#include <stdio.h>
#include <string.h>
#define MAX 100

void shiftString(char*);

int main(void)
{
    char input[MAX];

    scanf("%[^\n]", input);
    getchar();
    shiftString(input);

    return 0;
}

void shiftString(char* target)
{
    size_t len = strlen(target);
    char temp;
    int i, j;

    for (i = 0; i < len; i++)
    {
        puts(target);
        temp = *target;
        for (j = 0; j < len - 1; j++)
            target[j] = target[j + 1];
        target[len - 1] = temp;
    }
}