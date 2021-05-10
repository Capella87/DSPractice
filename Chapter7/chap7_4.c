#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

typedef int Data;
typedef int Top;

typedef struct _stack
{
    Data stk[MAX];
    Top t;
} Stack;

bool initStack(Stack*);
bool push(Stack*, const Data);
Data pop(Stack*);
Data peek(const Stack*);
int calc(char*); // Calculate expression

int main(void)
{
    char input[MAX + 1] = "";
    int n;

    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        scanf("%[^\n]", input);
        getchar();
        printf("%d\n", calc(input));
    }

    return 0;
}

bool initStack(Stack* s)
{
    s->t = -1;

    return true;
}

bool push(Stack* s, const Data d)
{
    if (s->t + 1 >= MAX) return false;
    s->stk[++s->t] = d;

    return true;
}

Data pop(Stack* s)
{
    if (s->t == -1) return -1;

    return s->stk[s->t--];
}

Data peek(const Stack* s)
{
    if (s->t == -1) return -1;

    return s->stk[s->t];
}

int calc(char* input)
{
    char* pos = input;
    size_t len = strlen(input);
    Stack num;
    Data a, b;

    initStack(&num);
    for (; pos < input + len; pos++)
    {
        if (*pos >= '0' && *pos <= '9') // operand
            push(&num, (int)(*pos - '0'));
        else // operator
        {
            b = pop(&num);
            a = pop(&num);

            switch (*pos)
            {
            case '+': // Addition
                push(&num, a + b);
                break;
            case '-': // Subtraction
                push(&num, a - b);
                break;
            case '*': // Multiplication
                push(&num, a * b);
                break;
            case '/': // Division
                push(&num, a / b);
                break;
            }
        }
    }

    return pop(&num);
}