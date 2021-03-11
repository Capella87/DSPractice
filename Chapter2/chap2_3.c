#include <stdio.h>
#include <stdlib.h>

double* prefixAverages1(int*, const int);
double* prefixAverages2(int*, const int);
void printResult(double*, const int);

int main(void)
{
    int n;

    scanf("%d", &n);
    getchar();
    int* input = (int*)malloc(sizeof(int) * n);
    if (input == NULL) exit(EXIT_FAILURE);
    for (int i = 0; i < n; i++)
        scanf("%d", &input[i]);
    printResult(prefixAverages1(input, n), n);
    printResult(prefixAverages2(input, n), n);

    free(input);
    return 0;
}

double* prefixAverages1(int* target, const int num)
{
    int i, j;
    double sum;
    double* output = (double*)malloc(sizeof(double) * num);
    if (output == NULL) exit(EXIT_FAILURE);

    for (i = 0; i < num; i++)
    {
        sum = 0.0;
        for (j = 0; j <= i; j++)
            sum += (double)target[j];
        output[i] = (int)(sum / (i + 1) + .5);
    }

    return output;
}

double* prefixAverages2(int* target, const int num)
{
    double sum = 0.0;
    double* output = (double*)malloc(sizeof(double) * num);
    if (output == NULL) exit(EXIT_FAILURE);

    for (int i = 0; i < num; i++)
    {
        sum += (double)target[i];
        output[i] = (int)(sum / (i + 1) + .5);
    }

    return output;
}

void printResult(double* target, const int num)
{
    for (int i = 0; i < num; i++)
        printf("%d ", (int)target[i]);
    putchar('\n');

    free(target);
}