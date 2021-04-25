#include <stdio.h>
#include <stdlib.h>

int processTriangle(int*, int); // 이항계수 삼각형을 처리하고 출력하는 함수

int main(void)
{
    int n; // 삼각형 1층의 배열 길이

    scanf("%d", &n); // 입력
    getchar();
    int* arrInput = (int*)malloc(sizeof(int) * n); // n만큼의 공간 할당
    if (arrInput == NULL) exit(EXIT_FAILURE);
    for (int i = 0; i < n; i++) // 배열 요소들을 입력받는다.
        scanf("%d", arrInput + i);
    processTriangle(arrInput, n); // 함수 호출

    return 0; // 메모리 할당 해제 기능은 밑의 함수에 있기 때문에 여기서는 따로 넣지 않는다.
}

int processTriangle(int* arr, int count) // 파스칼 삼각형 계산 및 출력 함수
{
    if (count <= 0) return -1; // 잘못된 수가 들어온 경우 종료
    if (count == 1) // 최상층 도달 시
    {
        printf(" %d", arr[0]); // 출력
        putchar('\n');
        free(arr); // 할당 해제

        return 0;
    }

    int* arr2 = (int*)malloc(sizeof(int) * (count - 1)); // 새로운 힙 공간에 배열 할당; 윗층이므로 요소 수가 하나 적어야 한다.
    if (!arr2) exit(EXIT_FAILURE);
    for (int i = 0; i < count - 1; i++) // 값 대입
        arr2[i] = arr[i] + arr[i + 1]; // 밑의 두 값을 더해 대입하면서 처리한다.
    processTriangle(arr2, count - 1); // 재귀; 함수 호출

    for (int i = 0; i < count; i++) // count == 1이 나온 경우 이후에 실행되는 부분으로 층에 해당되는 수를 출력
        printf(" %d", arr[i]);
    putchar('\n');
    free(arr); // 해당 층에 해당되는 배열 메모리 해제

    return 0;
}