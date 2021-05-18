#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define FLL 10
#define EMPY 11

typedef int Data;
typedef int Idx;

typedef struct _queue
{
    Data* arr;
    Idx f;
    Idx r;
    size_t size;
} Queue;

void getCommand(const int, const int);

bool initQueue(Queue*, const int q);
bool enqueue(Queue*, const Data);
Data dequeue(Queue*);
bool printQueue(const Queue*);
size_t currentCount(const Queue*);
bool isEmpty(const Queue*);
bool isFull(const Queue*);
void errHandler(Queue*, const int);

int main(void)
{
    int n, q;

    scanf("%d", &q);
    scanf("%d", &n);
    getchar();
    getCommand(q, n);

    return 0;
}

void getCommand(const int q, const int n)
{
    Queue a;
    char cmd;
    int num;

    initQueue(&a, q);
    for (int i = 0; i < n; i++)
    {
        scanf("%c", &cmd);
        switch (cmd)
        {
        case 'I':
            scanf("%d", &num);
            enqueue(&a, num);
            break;
        case 'P':
            printQueue(&a);
            break;
        case 'D':
            dequeue(&a);
            break;
        }
        getchar();
    }

    free(a.arr);
    return;
}

bool initQueue(Queue* target, const int q)
{
    target->arr = (Data*)malloc(sizeof(Data) * (size_t)q);
    if (!target->arr) return false;

    for (int i = 0; i < q; i++) // 모든 값을 0으로 초기화
        target->arr[i] = 0;
    target->f = target->r = 0;
    target->size = q;

    return true;
}

bool enqueue(Queue* q, const Data d)
{
    if (isFull(q))
        errHandler(q, FLL);
    q->r = (q->r + 1) % q->size;
    q->arr[q->r] = d;

    return true;
}

Data dequeue(Queue* q)
{
    if (isEmpty(q))
        errHandler(q, EMPY);
    Idx t = (q->f + 1) % q->size;
    Data e = q->arr[t];
    q->arr[t] = 0;
    q->f = t;

    return e;
}

bool printQueue(const Queue* q)
{
    if (isEmpty(q))
        return false;
    for (int i = 0; i < q->size; i++)
        printf(" %d", q->arr[i]);
    putchar('\n');

    return true;
}

size_t currentCount(const Queue* q)
{
    // rear index가 front보다 작은 경우 전자를, 그렇지 않은 경우 후자를 반환한다.
    return (q->r - q->f < 0) ? (size_t)(q->size + q->r - q->f) : (size_t)(q->r - q->f);
}

bool isEmpty(const Queue* q)
{
    return (q->r == q->f) ? true : false;
}

bool isFull(const Queue* q)
{
    return (currentCount(q) == (q->size - 1)) ? true : false;
}

void errHandler(Queue* q, const int errcode)
{
    switch (errcode)
    {
    case FLL:
        printf("overflow");
        printQueue(q);
        break;
    case EMPY:
        printf("underflow");
        printQueue(q);
        break;
    }
    free(q->arr);
    exit(EXIT_FAILURE);
}