#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
sem_t tabacoo, paper, matches, mediator;
void *Tabacoo_fun(void *agrs)
{
    while (1)
    {
        sem_wait(&tabacoo);
        printf("Smoker with tobacco has aquired tobacco\n");
        sem_wait(&matches);
        printf("Smoker with tobacco has aquired matches\n");
        printf("Smoker with tobacco is Smoking\n");
        sleep(1);
        sem_post(&mediator);
    }
}
void *Paper_fun(void *agrs)
{
    while (1)
    {
        sem_wait(&paper);
        printf("Smoker with paper has acquired paper\n");
        sem_wait(&matches);
        printf("Smoker with paper acquired matches\n");
        printf("Smoker with paper is Smoking\n");
        sleep(1);
        sem_post(&mediator);
    }
}
void *Matches_fun(void *agrs)
{
    while (1)
    {
        sem_wait(&tabacoo);
        printf("Smoker with matches has acquired tobacco\n");
        sem_wait(&paper);
        printf("Smoker with paper has acquired paper\n");
        printf("Smoker with matches is smoking\n");
        sleep(1);
        sem_post(&mediator);
    }
}
void *Mediator_fun(void *agrs)
{
    while (1)
    {
        sem_wait(&mediator);
        int random = rand() % 3;
        if (random == 0)
        {
            sem_post(&matches);
            sem_post(&paper);
            printf("Mediator has place Matches & Paper on the table\n");
        }
        else if (random == 1)
        {
            sem_post(&tabacoo);
            sem_post(&matches);
            printf("Mediator palce Tobacco & Matches on the tbale\n");
        }
        else
        {
            sem_post(&tabacoo);
            sem_post(&paper);
            printf("Mediator placed Tobacco & Paper on the table\n");
        }
    }
}
int main()
{
    srand(time(NULL));
    pthread_t Tabacoo, Paper, Matches, Mediator;
    
    sem_init(&tabacoo, 0, 0);
    sem_init(&paper, 0, 0);
    sem_init(&matches, 0, 0);
    sem_init(&mediator, 0, 1);

    pthread_create(&Tabacoo, NULL, &Tabacoo_fun, NULL);
    pthread_create(&Paper, NULL, &Paper_fun, NULL);
    pthread_create(&Matches, NULL, &Matches_fun, NULL);
    pthread_create(&Mediator, NULL, &Mediator_fun, NULL);

    pthread_join(Tabacoo, NULL);
    pthread_join(Paper, NULL);
    pthread_join(Matches, NULL);
    pthread_join(Mediator, NULL);

    sem_destroy(&tabacoo);
    sem_destroy(&paper);
    sem_destroy(&matches);
    sem_destroy(&mediator);

    return 0;
}