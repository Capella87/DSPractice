#include <stdio.h>
#include <stdlib.h>

int putData(int**, const int, const int);
void printData(const int**, const int, const int);

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

int putData(int** target, const int n, const int m)
{
    int num = 1;
    int i, j, x = 0, y = -1;
    int direction = 1;
    int iEnd = n - 1, jEnd = m;
    const int maxNum = n * m;

    while (num <= maxNum)
    {
        for (j = 0; j < jEnd; j++)
        {
            y += direction;
            target[x][y] = num++;
        }
        jEnd--;
        for (i = 0; i < iEnd; i++)
        {
            x += direction;
            target[x][y] = num++;
        }
        iEnd--;
        direction *= -1;
    }

    return 0;
}

void printData(const int** target, const int n, const int m)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            printf(" %d", target[i][j]);
        putchar('\n');
    }
}
