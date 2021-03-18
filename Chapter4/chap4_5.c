#include <stdio.h>
#include <stdlib.h>

int putData(int**, int, int);
void printData(int**, int, int);

int main(void)
{
    int n, m;
    int i;

    scanf("%d %d", &n, &m);
    int** arr = (int**)malloc(sizeof(int*) * n);
    if (arr == NULL) exit(EXIT_FAILURE);
    for (i = 0; i < n; i++) // 주의: 'n번' 할당해야 한다. Caution: Allocate spaces for n times
    {
        arr[i] = (int*)malloc(sizeof(int) * m); // Allocate (m * int) size space
        if (arr[i] == NULL) exit(EXIT_FAILURE);
    }
    putData(arr, n, m);
    printData(arr, n, m);

    for (i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
    return 0;
}

int putData(int** target, int n, int m)
{
    int x = 0, i = 0, y = 0, j = 0;
    int num = 1;
    const int max = n * m;

    target[0][0] = num++;
    while (num <= max)
    {
        if (y < m - 1)
            y++;
        else
            x++;
        j = y;
        i = x;
        while (j >= 0 && i < n)
            target[i++][j--] = num++;
    }
}

void printData(int** target, int n, int m) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            printf(" %d", target[i][j]);
        putchar('\n');
    }
}