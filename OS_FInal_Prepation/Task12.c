#include <wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
long count;
int flag[2] = {0, 0};
int turn = 0;
void *increment(void *ptr)
{
    for (unsigned int i = 0; i < 500000; i++)
    {
        flag[0] = 1;
        turn = 1;
        while (flag[1] == 1 && turn == 1)
        {
        }
        count++;
        flag[0] = 0;
    }
    pthread_exit(NULL);
}
void *decrement(void *ptr)
{
    for (unsigned int i = 0; i < 500000; i++)
    {
        flag[1] = 1;
        turn = 0;
        while (flag[0] == 1 && turn == 0)
        {
        }
        count--;
        flag[1] = 0;
    }
    pthread_exit(NULL);
}
int main()
{
    count = 3;
    printf("\nInitial value of Count is %ld ", count);
    pthread_t pid1, pid2;
    pthread_create(&pid1, NULL, &increment, NULL);
    pthread_create(&pid2, NULL, &decrement, NULL);
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    printf("\nFinal value of Count is %ld ", count);
    printf("\nIs it correct? \n");
    return 0;
}