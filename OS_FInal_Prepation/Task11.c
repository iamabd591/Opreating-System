#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int N, M;
void *fun(void *args)
{
    int index = (long)args;
    int *fac = (int *)malloc(sizeof(int));
    *fac = 1;
    for (int i = index + 1; i <= N; i += M)
    {
        *fac *= i;
    }
    printf("Thread no: %d, Factorial is %d\n", index, *fac);
    return (void *)fac;
}
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Too few Arguments Format like ./a.out N M where N and M is any Positive integers\n");
        return -1;
    }
    N = atoi(argv[1]);
    M = atoi(argv[2]);

    if (N < M)
    {
        printf("Invalid Input Format N must be greatr than M \n");
        return -1;
    }
    pthread_t pid[M];
    for (long i = 0; i < M; i++)
    {
        pthread_create(&pid[i], NULL, &fun, (void *)i);
    }

    int totalfac = 1, *thread_call = NULL;
    
    for (int i = 0; i < M; i++)
    {
        pthread_join(pid[i], (void *)&thread_call);
        totalfac *= *thread_call;
        free(thread_call);
    }
    printf("Total Factorial %d\n", totalfac);
    return 0;
}