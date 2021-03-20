#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define NAV 1

#ifdef _WIN32
#include <Windows.h>
#endif

double prefixAverages1(int*, double*, const int);
double prefixAverages2(int*, double*, const int);
void printResult(double*, const int);

int main(void)
{
#ifndef _WIN32
    exit(EXIT_FAILURE);
#endif

    int n, currentN;
    double m;
    int* x = NULL;
    double* output = NULL;
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    srand((unsigned int)time(NULL));

    scanf("%d", &n);

    puts("<version 1>");
    for (int i = 0; i < 10; i++)
    {
        currentN = (n / 10) * (i + 1);
        x = (int*)malloc(sizeof(int) * currentN);
        if (x == NULL) exit(EXIT_FAILURE);
        output = (double*)malloc(sizeof(double) * currentN);
        if (output == NULL) exit(EXIT_FAILURE);

        for (int j = 0; j < currentN; j++)
            x[j] = rand() % 10000 + 1;

        QueryPerformanceFrequency(&ticksPerSec);
        QueryPerformanceCounter(&start);
        m = prefixAverages1(x, output, currentN);
        QueryPerformanceCounter(&end);
        diff.QuadPart = end.QuadPart - start.QuadPart;
        printf("%d : %.6lf sec\n", currentN, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        free(x);
        free(output);
    }
    putchar('\n');

    puts("<version 2>");
    for (int i = 0; i < 10; i++)
    {
        currentN = (n / 10) * (i + 1);
        x = (int*)malloc(sizeof(int) * currentN);
        if (x == NULL) exit(EXIT_FAILURE);
        output = (double*)malloc(sizeof(double) * currentN);
        if (output == NULL) exit(EXIT_FAILURE);

        for (int j = 0; j < currentN; j++)
            x[j] = rand() % 10000 + 1;

        QueryPerformanceFrequency(&ticksPerSec);
        QueryPerformanceCounter(&start);
        m = prefixAverages2(x, output, currentN);
        QueryPerformanceCounter(&end);
        diff.QuadPart = end.QuadPart - start.QuadPart;
        printf("%d : %.6lf sec\n", currentN, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        free(x);
        free(output);
    }

    return 0;
}

double prefixAverages1(int* target, double* output, const int num)
{
    int i, j;
    double sum;
    double result;

    for (i = 0; i < num; i++)
    {
        sum = 0.0;
        for (j = 0; j <= i; j++)
            sum += (double)target[j];
        output[i] = (int)(sum / (i + 1) + .5);
    }
    result = output[num - 1];

    return result;
}

double prefixAverages2(int* target, double* output, const int num)
{
    double sum = 0.0;
    double result;

    for (int i = 0; i < num; i++)
    {
        sum += (double)target[i];
        output[i] = (int)(sum / (i + 1) + .5);
    }
    result = output[num - 1];

    return result;
}

void printResult(double* target, const int num)
{
    for (int i = 0; i < num; i++)
        printf("%d ", (int)target[i]);
    putchar('\n');

    free(target);
}