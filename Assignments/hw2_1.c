#include <stdio.h>

int getBinomial(int, int); // 이항계수 함수

int main(void)
{
    int n, k; // 입력받을 함수

    scanf("%d %d", &n, &k); // 값 입력
    printf("%d\n", getBinomial(n, k)); // 최종 반환값 출력

    return 0;   
}

int getBinomial(int n, int k) // 이항계수 함수
{
    if (k == 0 || k == n) // 값이 1인 경우 1을 반환
        return 1;
    else
        return getBinomial(n - 1, k - 1) + getBinomial(n - 1, k);
        // 이항계수 공식에 따라 반환
}