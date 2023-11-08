#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sysinfo.h>
typedef struct
{
    int *Arr;
    int Size;
} ThreadData;
void *Average(void *argu)
{
    ThreadData *data = (ThreadData *)argu;
    float sum = 0.0;
    for (int i = 0; i < data->Size; i++)
    {
        sum += data->Arr[i];
    }
    float *avg = (float *)malloc(sizeof(float));
    *avg = sum / data->Size;
    return (void *)avg;
}
void *mini(void *argu)
{
    ThreadData *data = (ThreadData *)argu;
    int *min = (int *)malloc(sizeof(int));
    *min = data->Arr[0];
    for (int i = 1; i < data->Size; i++)
    {
        if (*min > data->Arr[i])
        {
            *min = data->Arr[i];
        }
    }
    return (void *)min;
}
void *max(void *argu)
{
    ThreadData *data = (ThreadData *)argu;
    int *maxi = (int *)malloc(sizeof(int));
    *maxi = data->Arr[0];
    for (int i = 1; i < data->Size; i++)
    {
        if (*maxi < data->Arr[i])
        {
            *maxi = data->Arr[i];
        }
    }
    return (void *)maxi;
}
void *sorting(void *argu)
{
    ThreadData *data = (ThreadData *)argu;
    int *temp = (int *)malloc(sizeof(int));
    for (int i = 0; i < data->Size; i++)
    {
        for (int j = 0; j < data->Size; j++)
        {
            if (data->Arr[i] < data->Arr[j])
            {
                *temp = data->Arr[i];
                data->Arr[i] = data->Arr[j];
                data->Arr[j] = *temp;
            }
        }
    }
    return (void *)data->Arr;
}
void *Reverse(void *argu)
{
    ThreadData *data = (ThreadData *)argu;
    printf("Reverse of Array:");
    for (int i = data->Size - 1; i != -1; i--)
    {
        printf("%d ", data->Arr[i]);
    }
    printf("\n");
    pthread_exit(NULL);
}
int main(int argc, char **argv)
{

    if (argc < 2)
    {
        printf("Too Few Arguments\n");
        printf("Command line Format like ./a.out 1 2 3 4 5...\n");
        return -1;
    }
    int ArrSize = argc - 1;
    int *arr = (int *)malloc(ArrSize * sizeof(int));
    for (int i = 0; i < ArrSize; i++)
    {
        arr[i] = atoi(argv[i + 1]);
    }

    printf("Array is:");
    for (int i = 0; i < ArrSize; i++)
        printf("%d ", arr[i]);
    printf("\n");

    ThreadData data = {arr, ArrSize};
    pthread_t pid1, pid2, pid3, pid4, pid5;

    pthread_create(&pid1, NULL, &Average, (void *)&data);
    pthread_create(&pid2, NULL, &mini, (void *)&data);
    pthread_create(&pid3, NULL, &max, (void *)&data);
    pthread_create(&pid4, NULL, &sorting, (void *)&data);
    pthread_create(&pid5, NULL, &Reverse, (void *)&data);

    float *AvgAns = NULL;
    int *MiniAns, *MaxAns, *SortArr = NULL;
    pthread_join(pid1, (void *)&AvgAns);
    pthread_join(pid2, (void *)&MiniAns);
    pthread_join(pid3, (void *)&MaxAns);
    pthread_join(pid4, (void *)&SortArr);
    pthread_join(pid5, NULL);

    printf("Average is %f\n", *AvgAns);
    printf("Minimum is %d\n", *MiniAns);
    printf("Maximum is %d\n", *MaxAns);
    printf("Sorted Arr:");
    for (int i = 0; i < ArrSize; i++)
    {
        printf("%d ", SortArr[i]);
    }
    printf("\n");
    free(AvgAns);
    free(MiniAns);
    free(MaxAns);
    free(arr);

    return 0;
}