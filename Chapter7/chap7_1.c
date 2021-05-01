// Stack ADT implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ERR -1

typedef char Data;
typedef int Top;

typedef struct _stack
{
    Data* stk;
    size_t stkSize;
    Top t;
} Stack;

// Maintenance
bool initStack(Stack*, const size_t);
void process(Stack*, const int);

// Core
bool push(Stack*, const Data);
Data pop(Stack*);
void peek(Stack*);
bool duplicate(Stack*);
bool print(Stack*);
bool upRotate(Stack*, const int);
bool downRotate(Stack*, const int);


int main(void)
{
    Stack stack;
    int n, command_count;

    scanf("%d", &n);
    initStack(&stack, n);
    scanf("%d", &command_count);
    getchar();
    process(&stack, command_count);

    free(stack.stk);
    return 0;
}

void process(Stack* stack, const int cmd_count)
{
    char cmdInput[41];
    char* finder = 0;

    for (int i = 0; i < cmd_count; i++)
    {
        scanf("%[^\n]", cmdInput);
        getchar();
        finder = strchr(cmdInput, ' ');
        if (finder) *finder = '\0';

        if (!strcmp(cmdInput, "PUSH"))
            push(stack, cmdInput[5]);
        else if (!strcmp(cmdInput, "POP"))
            pop(stack);
        else if (!strcmp(cmdInput, "PEEK"))
            peek(stack);
        else if (!strcmp(cmdInput, "DUP"))
            duplicate(stack);
        else if (!strcmp(cmdInput, "UpR"))
            upRotate(stack, atoi(cmdInput + 4));
        else if (!strcmp(cmdInput, "DownR"))
            downRotate(stack, atoi(cmdInput + 6));
        else if (!strcmp(cmdInput, "PRINT"))
            print(stack);
    }
}

bool initStack(Stack* target, const size_t n)
{
    target->stk = (Data*)malloc(sizeof(Data) * n);
    if (!target->stk) return false;
    target->stkSize = n;
    target->t = ERR;

    return true;
}

bool push(Stack* target, const Data d)
{
    if (target->t == target->stkSize - 1)
    {
        puts("Stack FULL");
        return false;
    }

    target->t++;
    target->stk[target->t] = d;

    return true;
}

Data pop(Stack* target)
{
    if (target->t == ERR)
    {
        puts("Stack Empty");
        return ERR;
    }
    target->t--;

    return target->stk[target->t + 1];
}

void peek(Stack* target)
{
    if (target->t == ERR)
        puts("Stack empty");
    printf("%c\n", target->stk[target->t]);
}

bool duplicate(Stack* target)
{
    Data temp = pop(target);
    if (temp != ERR)
    {
        push(target, temp);
        push(target, temp);
    }

    return true;
}

bool print(Stack* target)
{
    if (target->t == -1)
        return false;
    for (int i = target->t; i >= 0; i--)
        printf("%c", target->stk[i]);
    putchar('\n');

    return true;
}

bool upRotate(Stack* target, const int n)
{
    if (n > target->t + 1) return false;
    Data temp = pop(target);
    Stack* tempStack = (Stack*)malloc(sizeof(Stack));
    initStack(tempStack, n - 1);
    for (int i = 0; i < n - 1; i++)
        push(tempStack, pop(target));
    push(target, temp);
    for (int i = 0; i < n - 1; i++)
        push(target, pop(tempStack));
    free(tempStack->stk);
    free(tempStack);

    return true;
}

bool downRotate(Stack* target, const int n)
{
    if (n > target->t + 1) return false;
    Data temp;
    Stack* tempStack = (Stack*)malloc(sizeof(Stack));
    initStack(tempStack, (size_t)(n - 1));
    for (int i = 0; i < n - 1; i++)
        push(tempStack, pop(target));
    temp = pop(target);
    for (int i = 0; i < n - 1; i++)
        push(target, pop(tempStack));
    push(target, temp);
    free(tempStack->stk);
    free(tempStack);

    return true;
}