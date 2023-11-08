#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#define fun_size 5
void *Average(void *argu)
{
    int *array = (int *)argu;
    float sum = 0;
    float *average = (float *)malloc(sizeof(float));

    for (int i = 0; i < fun_size; i++)
    {
        sum += array[i];
    }
    printf("SUM is %f\n", sum);
    *average = sum / fun_size;
    return average;
}

void *Minimum(void *argu)
{
    int *array = (int *)argu;
    int m = array[0];
    int *mini = (int *)malloc(sizeof(int));

    for (int i = 0; i < fun_size; i++)
    {
        if (m > array[i])
        {
            m = array[i];
        }
    }
    *mini = m;
    return mini;
}
void *Maximum(void *argu)
{
    int *array = (int *)argu;
    int m = array[0];
    int *max = (int *)malloc(sizeof(int));
    for (int i = 0; i < fun_size; i++)
    {
        if (m < array[i])
        {
            m = array[i];
        }
    }
    *max = m;
    return max;
}
void *Sort(void *argu)
{
    int *array = (int *)argu;
    int temp = 0;
    for (int i = 0; i < fun_size; i++)
    {
        for (int j = i + 1; j < fun_size; j++)
        {
            if (array[i] > array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    printf("Ascending Order ");
    for (int i = 0; i < fun_size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    for (int i = 0; i < fun_size; i++)
    {
        for (int j = i + 1; j < fun_size; j++)
        {
            if (array[i] < array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    printf("Decending order ");
    for (int i = 0; i < fun_size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void *Reverse(void *argu)
{
    int *array = (int *)argu;
    int temp = 0;
    for (int i = 0, j = fun_size - 1; i < fun_size / 2; i++, j--)
    {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    printf("Reverse Array ");
    for (int i = 0; i < fun_size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("INVALID COMMAND LINE ARGUMENTS\n");
        return -1;
    }
    int size = argc - 1;
    int *arr = (int *)malloc(sizeof(int));
    for (int i = 0; i < size; i++)
    {
        arr[i] = atoi(argv[i + 1]);
    }
    printf("Given Array is:");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    pthread_t tid1, tid2, tid3, tid4, tid5;
    void *ret, *ret2, *ret3, *ret4;
    pthread_create(&tid1, NULL, &Average, (void *)&arr[0]);
    pthread_create(&tid2, NULL, &Minimum, (void *)&arr[0]);
    pthread_create(&tid3, NULL, &Maximum, (void *)&arr[0]);
    pthread_create(&tid4, NULL, &Sort, (void *)&arr[0]);
    pthread_create(&tid5, NULL, &Reverse, (void *)&arr[0]);

    pthread_join(tid1, &ret);
    pthread_join(tid2, &ret2);
    pthread_join(tid3, &ret3);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);

    float ans = *((float *)ret);
    int min = *((int *)ret2);
    int max = *((int *)ret3);
    printf("Average of Array is %f\n", ans);
    printf("Minimum of Array is %d\n", min);
    printf("Maximum of Array is %d\n", max);
    // pthread_exit(0);

    return 0;
}
