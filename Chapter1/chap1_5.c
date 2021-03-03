#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _time
{
    int hour;
    int minute;
    int second;
} Time;

Time* diffTime(const Time*, const Time*);

int main(void)
{
    Time a, b,*result;

    scanf("%d %d %d", &a.hour, &a.minute, &a.second);
    scanf("%d %d %d", &b.hour, &b.minute, &b.second);
    result = diffTime(&a, &b);
    printf("%d %d %d\n", result->hour, result->minute, result->second);

    free(result);
    return 0;
}

Time* diffTime(const Time* a, const Time* b)
{
    int a_sec, b_sec;
    int result_sec;
    Time* result = (Time*)malloc(sizeof(Time));
    if (result == NULL) exit(EXIT_FAILURE);

    b_sec = b->hour * 3600 + b->minute * 60 + b->second;
    a_sec = a->hour * 3600 + a->minute * 60 + a->second;
    result_sec = b_sec - a_sec;
    result->hour = result_sec / 3600;
    result->minute = (result_sec % 3600) / 60;
    result->second = result_sec % 3600 % 60;

    return result;
}