// Stack ADT implementation based on linked list

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char Data;
typedef int Top;

const char* openBracket = "{[(";
const char* closeBracket = "}])";

typedef struct _node
{
    Data bracket;
    struct _node* next;
} Node;

typedef struct _list
{
    Node* tHead;
    int nodeCount;
} Stack;

bool stackInit(Stack*);
bool push(Stack*, const Data);
Data pop(Stack*);
Data peek(const Stack*);
bool isEmpty(Stack*);
bool isBalanced(Stack* target);
bool isCounterpart(const Data, const Data);
bool freeStack(Stack*);

int main(void)
{
    Stack stk;
    stackInit(&stk);

    isBalanced(&stk);
    freeStack(&stk);
    return 0;
}

bool stackInit(Stack* target)
{
    target->tHead = NULL;
    target->nodeCount = 0;

    return true;
}

bool push(Stack* target, const Data d)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->bracket = d;
    newNode->next = target->tHead;
    target->tHead = newNode;
    target->nodeCount++;

    return true;
}

Data pop(Stack* target)
{
    if (!target->tHead) return -1;

    Node* pos = target->tHead;
    Data d = pos->bracket;
    target->tHead = pos->next;
    target->nodeCount--;
    free(pos);

    return d;
}

Data peek(const Stack* target)
{
    if (!target->tHead) return -1;

    return target->tHead->bracket;
}

bool isEmpty(Stack* target)
{
    if (!target->tHead) return true;
    else return false;
}

bool isBalanced(Stack* target)
{
    char input[1001];
    char* pos = input;
    int bracketCount = 0;
    bool isbal = true;

    scanf("%[^\n]", input);
    getchar();
    size_t size = strlen(input);
    for (; pos < input + size; pos++)
    {
        if (strchr(openBracket, *pos))
        {
            push(target, *pos);
            bracketCount++;
        }
        else if (strchr(closeBracket, *pos))
        {
            if (isEmpty(target))
                isbal = false;
            else
            {
                Data t = pop(target);
                if (!isCounterpart(t, *pos))
                    isbal = false;
            }
            bracketCount++;
        }
    }
    if (!isEmpty(target)) isbal = false; // 스택에 남아 있는 경우(짝짝이) false로 바꾼다.
    printf("%s_%d\n", (!isbal) ? "Wrong" : "OK", bracketCount);

    return true;
}

bool freeStack(Stack* target)
{
    if (!target->tHead) return true;

    while (target->tHead)
        pop(target);

    return true;
}

bool isCounterpart(const Data open, const Data close)
{
    if (open == '{' && close == '}') return true;
    else if (open == '(' && close == ')') return true;
    else if (open == '[' && close == ']') return true;
    else return false;
}