#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
void *Child(void *argu)
{
    char* msg=(void*)argu;
    printf("Recived from main %s \n",msg);
    return NULL;
}
int main()
{
    char* message = "Hello Child thread how are you?";
    pthread_t pid;
    pthread_create(&pid,NULL,&Child,(void*)message);
    pthread_join(pid,NULL);
    printf("Child thread returns\n");
    return 0;
}