#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack
{
    int* arr;
    int n, top;
} Stack;

typedef struct queue
{
    Stack S1, S2;
} Queue;

// Stack 함수
bool init_stack(Stack* stk, const int n);
bool isEmpty(const Stack* stk);
bool isFull(const Stack* stk);
bool push(Stack* stk, const int data);
int pop(Stack* stk);
bool deallocStack(Stack* stk);

// Queue 함수
bool initQueue(Queue* q, const int s1_size, const int s2_size);
bool enqueue(Queue* q, const int data);
int dequeue(Queue* q);
bool deallocQueue(Queue* q);

int main(void)
{
    Queue Q;
    int n1, n2, calc, input;
    char command;

    scanf("%d %d", &n1, &n2); // 각각 S1과 S2의 크기를 입력받음
    initQueue(&Q, n1, n2); // Queue 초기화
    scanf("%d", &calc); // 연산의 개수
    getchar();

    for (int i = 0; i < calc; i++) // 연산 개수만큼 수행
    {
        scanf("%c", &command);
        switch (command)
        {
        case 'E': // Enqueue
            scanf("%d", &input);
            enqueue(&Q, input);
            break;
        case 'D': // Dequeue
            dequeue(&Q);
        }
        getchar();
    }

    deallocQueue(&Q); // Queue 동적 할당(Queue 내 Stack) 해제
        return 0;
}

bool init_stack(Stack* stk, const int n) // 스택 초기화
{
    stk->arr = (int*)malloc(sizeof(int) * n); // 동적 할당
    stk->n = n; // 최대 크기
    stk->top = -1; // top 초기화

    return true;
}

bool isEmpty(const Stack* stk) // 비어 있는 스택이면 true를, 그렇지 않다면 false 반환
{
    return stk->top == -1 ? true : false;
}

bool isFull(const Stack* stk) // 꽉 차있다면 true를, 그렇지 않다면 false 반환
{
    return stk->top + 1 == stk->n ? true : false;
}

bool push(Stack* stk, const int data) // 값 집어 넣기
{
    if (isFull(stk)) // 꽉 차 있으면 함수 종료
        return false;

    stk->arr[++stk->top] = data;
    return true;
}

int pop(Stack* stk) // 값 빼기
{
    return isEmpty(stk) ? -1 : stk->arr[stk->top--]; // 비어 있다면 -1를 반환하고 그렇지 않다면 꺼낸 값을 반환
}

bool deallocStack(Stack* stk) // 스택 동적 할당 해제
{
    free(stk->arr);
    stk->n = 0;

    return true;
}

bool initQueue(Queue* q, const int s1_size, const int s2_size) // 큐 초기화
{
    return init_stack(&q->S1, s1_size) && init_stack(&q->S2, s2_size); // 큐 내의 두 스택 초기화
}

bool enqueue(Queue* q, const int data) // 값 집어 넣기
{
    int moveCount = 0;

    if (isFull(&q->S1) && isEmpty(&q->S2)) // S1이 차있지만 S2가 비어있는 경우 S1내 데이터를 S2로 이동
    {
        while (!isEmpty(&q->S1) && !isFull(&q->S2)) // S1에서 모든 원소를 꺼내 S2에 넣는다.
        {
            push(&q->S2, pop(&q->S1));
            moveCount++;
        } 
    } // 조건에서는 늘 n1(S1 크기) <= n2 이므로 다 못들어갈 일은 없다.
    else if (isFull(&q->S1) && !isEmpty(&q->S2)) // S1이 차있고 S2도 비어있지 않은 경우
    {
        puts("overflow"); // "overflow"라 출력한 후 함수 종료
        return false;
    }
    push(&q->S1, data);
    printf("+ %d %d\n", data, moveCount); // 넣은 원소와 옮겨진 횟수 출력

    return true;
}

int dequeue(Queue* q) // 값 빼기
{
    int moveCount = 0;
    int rt;

    if (isEmpty(&q->S2) && !isEmpty(&q->S1)) // S1은 비어있지 않고 S2만 비어 있는 경우
    {
        while (!isEmpty(&q->S1)) // 일단 S1에서 모든 원소를 꺼내 S2로 옮긴다.
        {
            push(&q->S2, pop(&q->S1));
            moveCount++;
        }
    }
    else if (isEmpty(&q->S2) && isEmpty(&q->S2)) // 두 스택 모두 비어 있는 경우
    {
        puts("underflow"); // "underflow" 라 출력 후 함수 종료
        return -1;
    }
    rt = pop(&q->S2); // S2에서 한번 꺼낸다.
    printf("- %d %d\n", rt, moveCount); // 꺼낸 원소와 옮겨진 횟수 출력

    return rt;
}

bool deallocQueue(Queue* q) // Queue 동적 할당 해제
{
    return deallocStack(&q->S1) && deallocStack(&q->S2); // 둘 다 정상적으로 이루어지면 true를 반환한다.
}