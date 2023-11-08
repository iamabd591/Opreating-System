#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define No_of_readers 3
#define No_of_writer 2
sem_t mutex, resources, serviceQueue;
int readerCount = 0, writerCount = 0;
void *Reader(void *args)
{
    int readerId = *(int *)args;
    while (1)
    {
        sem_wait(&mutex);
        sem_wait(&serviceQueue);
        readerCount++;
        if (readerCount == 1)
        {
            sem_wait(&resources);
        }
        sem_post(&mutex);
        sem_post(&serviceQueue);

        printf("Reader %d is Reading.\n", readerId);
        sleep(1);
        sem_wait(&mutex);
        readerCount--;
        if (readerCount == 0)
        {
            sem_post(&resources);
        }
        sem_post(&mutex);
    }
}
void *Writer(void *args)
{
    int writerId = *(int *)args;
    while (1)
    {
        sem_wait(&serviceQueue);
        sem_wait(&resources);
        printf("Writer %d is writing.\n", writerId);
        sleep(1);
        sem_post(&resources);
        sem_post(&serviceQueue);
    }
}
int main()
{
    pthread_t Readers[No_of_readers], Writers[No_of_writer];
    int readerIDs[No_of_readers], writerIDs[No_of_writer];

    sem_init(&mutex, 0, 1);
    sem_init(&resources, 0, 1);
    sem_init(&serviceQueue, 0, 1);

    for (int i = 0; i < No_of_readers; i++)
    {
        readerIDs[i] = i + 1;
        pthread_create(&Readers[i], NULL, Reader, (void *)&readerIDs[i]);
    }

    for (int i = 0; i < No_of_writer; i++)
    {
        writerIDs[i] = i + 1;
        pthread_create(&Writers[i], NULL, Writer, (void *)&writerIDs[i]);
    }

    for (int i = 0; i < No_of_readers; i++)
    {
        pthread_join(Readers[i], NULL);
    }
    for (int i = 0; i < No_of_writer; i++)
    {
        pthread_join(Writers[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&resources);
    sem_destroy(&serviceQueue);
    return 0;
}