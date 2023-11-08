#define fun_size 20
#define _GNU_SOURCE
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/sysinfo.h>
void *sorting(void *argu)
{
    int *array = (int *)argu;
    int temp = 0;
    for (int i = 0; i < fun_size; i++)
    {
        for (int j = i + 1; j < fun_size; j++)
        {
            if (i % 2 == 0)
            {
                if (array[i] > array[j])
                {
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
            else
            {
                if (array[i] > array[j])
                {
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }
    printf("AFTER SORTING:");
    for (int i = 0; i < fun_size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        printf("COMMAND LINE ARGUMENTS IS INVALID\n");
        return -1;
    }
    int size = atoi(argv[1]);
    if (size <= 0)
    {
        printf("INVALID SIZE\n");
        return -1;
    }
    int *arr = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
        arr[i] = rand() % 30;

    printf("Given Array is:");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    int proc = get_nprocs();
    printf("CURRENTLY AVAILABLE PROCESSORS:%d\n", proc);

    printf("PROCESSES CONFIGURE:");
    int proces = get_nprocs_conf();
   
    for (int i = 0; i < proces; i++)
        printf("%d ", i);
    printf("\n");

    printf("CURRENTLY RUNNING ON CPU NO %d\n", sched_getcpu());

    int select = 0;
    printf("PLEASE SELECT CPU:");
    scanf("%d", &select);
    if (select < 0 || select > proces)
    {
        printf("INVALID CPU SELECT\n");
        return -1;
    }

    cpu_set_t mycpu;
    CPU_ZERO(&mycpu);
    CPU_SET(select, &mycpu);
    sched_getaffinity(0, sizeof(cpu_set_t), &mycpu);

    pthread_t tid1, tid2;
    printf("NOW RUNNING ON CPU NO %d\n", sched_getcpu());
    pthread_create(&tid1, NULL, &sorting, (void *)&arr[0]);
    pthread_create(&tid2, NULL, &sorting, (void *)&arr[0]);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_exit(0);
    free(arr);
    return 0;
}