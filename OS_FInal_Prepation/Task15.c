#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
sem_t full, empty;
int n = 10;
int in = 0, out = 0;
int buffer[10];
void *Producer(void *args)
{
    for (unsigned int i = 1; i < 115; i++)
    {
        sem_wait(&empty);
        buffer[in] = i;
        in = (in + 1) % n;
        sem_post(&full);
    }
    pthread_exit(NULL);
}
void *Consumer(void *args)
{
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    for (unsigned int i = 1; i < 15; i++)
    {
        sem_wait(&full);
        printf("%d ", buffer[out]);
        out = (out + 1) % n;
        sem_post(&empty);
    }
    printf("\n");
    pthread_exit(NULL);
}
int main()
{
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 10);

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, &Producer, NULL);
    pthread_create(&tid2, NULL, &Consumer, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}