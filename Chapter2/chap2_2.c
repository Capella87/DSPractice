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

    while (1)
    {
        while (arr[i][j] == 1 && j < n) // 0이 나올 때까지 오른쪽으로 이동
            j++;
        if (j == n) return i; // 마지막 행에 도달하기 전에 마지막 열에 도달한 경우
        result = i;
        while (arr[i][j] == 0 && i < n) // 1이 나올 때까지 계속 밑으로 이동
            i++;
        if (i == n) return result;  // 마지막 행에 도달한 경우
    }

    return result;
}

// Big-O : 2n (worst case) -> O(n)