#include <stdio.h>
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

    while (i < n && j < n)
    {
        if (arr[i][j] == 0) // 0이면 아래 행으로 이동
            i++;
        else
        {
            result = i;
            j++;
        }
    }

    return result;
}

// Big-O : 2n (worst case) -> O(n)