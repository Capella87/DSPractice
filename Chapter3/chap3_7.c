#include <stdio.h>
#define MAX 100

int getCount(char*, const char);

int main(void)
{
    char input[MAX + 1];
    char ctarget;

    scanf("%[^\n]", input);
    getchar();
    scanf("%c", &ctarget);
    printf("%d\n", getCount(input, ctarget));

    return 0;
}

int getCount(char* target, const char element)
{
    static int tcount = 0;

    if (*target == '\0')
        return tcount;
    else if (*target == element)
        tcount++;
    getCount(target + 1, element);

    return tcount;
}