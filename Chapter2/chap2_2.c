#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

int mostOnes(int[][MAX], int);

int main(void)
{
    int arr[MAX][MAX];
    int n;

    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);
        getchar();
    }
    printf("%d\n", mostOnes(arr, n));

    return 0;
}

int mostOnes(int arr[][MAX], int n)
{
    int i = 0, j = 0;
    int result = 0;
    bool acrossOne = false;

    while (1)
    {

        if (!acrossOne && arr[i][j] == 1) acrossOne = true;
        while ((j < n - 1) && (arr[i][j] == 1))
            j++;
        if (acrossOne)
        {
            result = i;
            acrossOne = false;
        }
        if (i == n - 1 || j == n - 1) break;
        // 마지막 줄 도달 이전에 최대 열까지 도달해도 루프에서 빠져 나온다.
        while (arr[i][j] == 0 && i < n - 1)
            i++;
    }

    return result;
}