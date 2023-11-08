#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include<stdlib.h>
void *add(void *argu)
{
    int *value = (int *)malloc(sizeof(int));
    int *num = (int *)argu;
    *value = num[0] + num[1];
    return value;
}
int main()
{

    pthread_t pid1, pid2, pid3;
    void *ret1, *ret2, *ret3;
    int arr[] = {10, 20, 30, 40, 50, 60};
    pthread_create(&pid1, NULL, &add, (void *)&arr[0]);
    pthread_create(&pid2, NULL, &add, (void *)&arr[2]);
    pthread_create(&pid3, NULL, &add, (void *)&arr[4]);

    pthread_join(pid1, &ret1);
    pthread_join(pid2, &ret2);
    pthread_join(pid3, &ret3);

    int ans = *((int *)ret1) + *((int *)ret2) + *((int *)ret3);
    printf("Sum is %d\n", ans);
    return 0;
}