#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

typedef char Symbol;
typedef int Top;
typedef char Data;

const char* operators = "|&<>-+/*!";
const int priority[9] = { 1, 2, 3, 3, 4, 4, 5, 5, 6 };

typedef struct _stack
{
    char* stk;
    Top t;
} Stack;

void initStack(Stack* s);
bool push(Stack* s, const char* sy);
bool isEmpty(const Stack* s);
char pop(Stack* s);
char peek(const Stack* s);
void getInfix(const int n);
int getPriority(char* target);
bool convertToPostfix(char* input, Stack* s);

int main(void)
{
    int n;

    scanf("%d", &n);
    getchar();
    getInfix(n);

    return 0;
}

void initStack(Stack* s) // Stack Initialization
{
    s->stk = (char*)malloc(sizeof(char) * (MAX + 1));
    s->t = -1;
}

bool push(Stack* s, const char* sy)
{
    if (s->t + 1 >= MAX || *sy == '\0')
        return false;
    s->stk[++s->t] = *sy;

    return true;
}

bool isEmpty(const Stack* s) // Return true if the stack is vacant
{
    return (s->t == -1) ? true : false;
}

char pop(Stack* s) // Remove the last-in element from stack
{
    if (s->t == -1)
        return 0;
    return s->stk[s->t--];
}

char peek(const Stack* s) // Return the value of last-in element without removal
{
    if (s->t == -1) return 0;
    return s->stk[s->t];
}

void getInfix(const int n) // get infix expression and convert
{
    char input[MAX + 1] = "";
    Stack s;

    initStack(&s);
    for (int i = 0; i < n; i++)
    {
        scanf("%[^\n]", input);
        convertToPostfix(input, &s);
        getchar();
        putchar('\n');
    }
    free(s.stk);
}

int getPriority(char* target) // Return priority
{
    if (*target == '\0') return -1;
    else if (*target == '(') return 0;
    else return priority[strchr(operators, *target) - operators]; // Use pointer difference for index.
}

bool convertToPostfix(char* input, Stack* s) // Convert infix to postfix expression
{
    char* p = input;
    Stack prior;
    size_t len = strlen(input); // for loop
    char temp;

    initStack(&prior);
    for (; p <= input + len; p++)
    {
        if (!strchr(operators, *p) && !strchr("()", *p)) // Operand
            printf("%c", *p);
        else if (*p == '(')
        {
            push(s, p);
            push(&prior, "0");
        }
        else if (*p == ')')
        {
            while (peek(s) != '(')
            {
                temp = pop(s);
                pop(&prior); // save priority information
                putchar(temp);
                if (temp == '&' || temp == '|') // For operator || and &&
                    putchar(temp);
            }
            pop(s);
            pop(&prior);
        }
        else if (strchr("+-", *p) && ((p - input) == 0 || strchr(operators, *(p - 1)))) // Negative and positive operator
        {
            push(s, p);
            push(&prior, "6"); // Different priority to plus and minus operator
        }
        else
        {
            while (!isEmpty(s))
            {
                if (getPriority(p) > (int)(peek(&prior) - '0'))
                    break;
                temp = pop(s);
                pop(&prior); // Get rid of priority information of the operator
                if (temp == '&' || temp == '|')
                    putchar(temp);
                putchar(temp);
            }
            push(s, p);
            temp = '0' + (char)getPriority(p);
            push(&prior, &temp);
            if (*p == '&' || *p == '|')
                p++;
        }
    }

    free(prior.stk);
    return true;
}