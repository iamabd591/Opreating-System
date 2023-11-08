#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define Num_Philisopher 5
typedef enum
{
    THINKING,
    HUNGRY,
    EATING
} P_state;
P_state p_data[Num_Philisopher];
sem_t forks[Num_Philisopher];
sem_t mutex;
int getleft(int i)
{
    return i;
}
int getright(int i)
{
    return (i + 1) % Num_Philisopher;
}
void test(int i)
{
    if (p_data[i] == HUNGRY && p_data[getleft(i) != EATING] && p_data[getright(i) != EATING])
    {
        p_data[i] = EATING;
        sem_post(&forks[i]);
    }
}
void takeforks(int i)
{
    sem_wait(&mutex);
    p_data[i] = HUNGRY;
    test(i);
    sem_post(&mutex);
    sem_wait(&forks[i]);
}
void putforks(int i)
{
    sem_wait(&mutex);
    p_data[i] = THINKING;
    test(getleft(i));
    test(getright(i));
    sem_post(&mutex);
}
void *philisopher(void *args)
{
    int philisopher_index = *(int *)args;
    while (1)
    {
        printf("Philisopher %d is THINKING\n", philisopher_index);
        takeforks(philisopher_index);
        printf("Philisopher %d is EATING\n", philisopher_index);
        sleep(1);
        putforks(philisopher_index);
    }
}
int main()

{
    int P_Indices[Num_Philisopher];
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < Num_Philisopher; i++)
    {
        sem_init(&forks[i], 0, 0);
        p_data[i] = THINKING;
    }
    pthread_t tid[Num_Philisopher];
    for (int i = 0; i < Num_Philisopher; i++)
    {
        P_Indices[i] = i;
        pthread_create(&tid[i], NULL, philisopher, (void *)&P_Indices[i]);
    }

    for (int i = 0; i < Num_Philisopher; i++)
    {
        pthread_join(tid[i], NULL);
    }
    sem_destroy(&mutex);
    for (int i = 0; i < Num_Philisopher; i++)
    {
        sem_destroy(&forks[i]);
    }
    return 0;
}