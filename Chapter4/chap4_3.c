#include <stdio.h>

void printResult(const int);

int main(void)
{
    int n;

    scanf("%d", &n);
    printResult(n);

    return 0;
}

void printResult(const int n)
{
    int i = 0, j = 0, num = 1;
    const int final = n * n;
    int control = (i / n) % 2;

    while (i < final)
    {
        if (!control)
        {
            printf(" %d", num++);
            i++;
        }
        else
        {
            printf(" %d", num--);
            i++;
        }
        if (i % n == 0 && i != 0)
        {
            putchar('\n');
            num += n;
            num += control == 0 ? -1 : 1;
            control = (i / n) % 2;
        }
    }
}