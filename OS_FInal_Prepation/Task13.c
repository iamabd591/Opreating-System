#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <wait.h>
#define Max_Size 100
int N, M;
int MatrixA[Max_Size][Max_Size], MatrixB[Max_Size][Max_Size], Resulted[Max_Size][Max_Size];
typedef struct
{
    int row;
} ThreadData;
void *MatrixSum(void *args)
{
    ThreadData *data = (ThreadData *)args;
    int row = data->row;
    for (int j = 0; j < M; j++)
    {
        Resulted[row][j] = MatrixA[row][j] + MatrixB[row][j];
    }
    pthread_exit(NULL);
}
int main(int argc, char **argv)
{
    if (argc < 3 || argc > 3)
    {
        printf("Command Line Format in Incorrect\n");
        printf("Format like ./a.out N M Where N & M is any positive intergers\n");
        return -1;
    }
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    if (N <= 0 || M <= 0 || N > Max_Size || M > Max_Size)
    {
        printf("Some of your input value is invalid\n");
        return -1;
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            MatrixA[i][j] = rand() % 10;
            MatrixB[i][j] = rand() % 10;
        }
    }
    printf("Matrix A is");
    for (int i = 0; i < N; i++)
    {
        printf("\n");
        for (int j = 0; j < M; j++)
        {
            printf("%d ", MatrixA[i][j]);
        }
    }
    printf("\n");
    printf("\n");

    printf("Matrix B is");
    for (int i = 0; i < N; i++)
    {
        printf("\n");
        for (int j = 0; j < M; j++)
        {
            printf("%d ", MatrixB[i][j]);
        }
    }
    printf("\n");
    printf("\n");

    pthread_t tid[N];
    ThreadData data[N];
    for (int i = 0; i < N; i++)
    {
        data[i].row = i;
        pthread_create(&tid[i], NULL, &MatrixSum, (void *)&data[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(tid[i], NULL);
    }
    printf("Resulted Matrix");
    for (int i = 0; i < N; i++)
    {
        printf("\n");
        for (int j = 0; j < M; j++)
        {
            printf("%d ", Resulted[i][j]);
        }
    }
    printf("\n");
    printf("\n");

    return 0;
}