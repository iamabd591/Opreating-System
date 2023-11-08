#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
void * ChildThread(void *argu)
{
    while(1)
    {
        printf("X\n");
        fflush(stdout);
    }
}
int main()
{
pthread_t pid;
pthread_create(&pid,NULL,&ChildThread,(void* )NULL);

while(1)
{
    printf("O\n");
    fflush(stdout);
}
    return 0;
}