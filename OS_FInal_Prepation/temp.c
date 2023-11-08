#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t tobacco, paper, matches, mediator;

void *smokerWithTobacco(void *arg)
{
    while (1)
    {
        sem_wait(&tobacco);
        printf("Smoker with tobacco has acquired tobacco.\n");
        sem_wait(&matches);
        printf("Smoker with tobacco has acquired matches.\n");

        // Smoke the cigarette
        printf("Smoker with tobacco is smoking.\n");
        sleep(1);

        // Signal the mediator that smoking is done
        sem_post(&mediator);
    }
}

void *smokerWithPaper(void *arg)
{
    while (1)
    {
        sem_wait(&paper);
        printf("Smoker with paper has acquired paper.\n");
        sem_wait(&matches);
        printf("Smoker with paper has acquired matches.\n");

        // Smoke the cigarette
        printf("Smoker with paper is smoking.\n");
        sleep(1);

        // Signal the mediator that smoking is done
        sem_post(&mediator);
    }
}

void *smokerWithMatches(void *arg)
{
    while (1)
    {
        sem_wait(&tobacco);
        printf("Smoker with matches has acquired tobacco.\n");
        sem_wait(&paper);
        printf("Smoker with matches has acquired paper.\n");

        // Smoke the cigarette
        printf("Smoker with matches is smoking.\n");
        sleep(1);

        // Signal the mediator that smoking is done
        sem_post(&mediator);
    }
}

void *mediator_fun(void *arg)
{
    while (1)
    {
        sem_wait(&mediator);

        // Randomly choose two ingredients
        int random = rand() % 3;
        if (random == 0)
        {
            sem_post(&paper);
            sem_post(&matches);
            printf("Mediator has placed paper and matches on the table.\n");
        }
        else if (random == 1)
        {
            sem_post(&tobacco);
            sem_post(&matches);
            printf("Mediator has placed tobacco and matches on the table.\n");
        }
        else if(random==2)
        {
            sem_post(&tobacco);
            sem_post(&paper);
            printf("Mediator has placed tobacco and paper on the table.\n");
        }
        else {
            exit(0);
        }
    }
}

int main()
{
    srand(time(NULL));

    pthread_t smoker1, smoker2, smoker3, mediatorThread;

    // Initialize the semaphores
    sem_init(&tobacco, 0, 0);
    sem_init(&paper, 0, 0);
    sem_init(&matches, 0, 0);
    sem_init(&mediator, 0, 1);

    // Create the smoker threads
    pthread_create(&smoker1, NULL, &smokerWithTobacco, NULL);
    pthread_create(&smoker2, NULL, &smokerWithPaper, NULL);
    pthread_create(&smoker3, NULL, &smokerWithMatches, NULL);

    // Create the mediator thread
    pthread_create(&mediatorThread, NULL, &mediator_fun, NULL);

    // Wait for the threads to finish (this will never happen as the threads run infinitely)
    pthread_join(smoker1, NULL);
    pthread_join(smoker2, NULL);
    pthread_join(smoker3, NULL);
    pthread_join(mediatorThread, NULL);

    // Destroy the semaphores
    sem_destroy(&tobacco);
    sem_destroy(&paper);
    sem_destroy(&matches);
    sem_destroy(&mediator);

    return 0;
}
