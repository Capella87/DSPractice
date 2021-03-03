#include <stdio.h>
#define SIZE 10

void ABC(int[], int);

int main(void)
{
    int input[SIZE];
    int i;

    for (i = 0; i < SIZE; i++)
        scanf("%d", input + i);
    for (i = 1; i <= SIZE; i++)
        ABC(input, i);
    for (i = 0; i < SIZE; i++)
        printf(" %d", *(input + i));
    putchar('\n');
    return 0;
}

void ABC(int target[], int k)
{
    int* pos = target + k - 1;
    int* max = target + k - 1;
    int temp;

    for (; pos < target + SIZE; pos++)
        if (*pos > *max) max = pos;
    pos = target + k - 1;
    if (max != pos)
    {
        temp = *max;
        *max = *pos;
        *pos = temp;
    }
}