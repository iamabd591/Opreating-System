#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t mutex;
int count = 0, in = 0, out = 0;
int  n = 10;
int buffer[10];
void *producer(void *args)
{
    for (unsigned int i = 1; i < 15; i++)
    {
        while (count == n)
            ;
        buffer[n] = i;
        in = (in + 1) % n;
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}
void *consumer(void *args)
{
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    for (int i = 1; i < 15; i++)
    {
        while (count == 0)
            ;
        printf("%d ", buffer[out]);
        out = (out + 1) % n;
        pthread_mutex_lock(&mutex);
        count--;
        pthread_mutex_unlock(&mutex);
    }
    printf("\n");
    pthread_exit(NULL);
}
int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, &producer, NULL);
    pthread_create(&tid2, NULL, &consumer, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}