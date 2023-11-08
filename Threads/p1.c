#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <pthread.h>
#include <sys/sysinfo.h>
void *add(void *argu)
{
    int *value = (int *)malloc(sizeof(int));
    int *num = (int *)argu;
    *value = num[0] + num[1];
    return value;
}
int main()
{
    int numbers[] = {10, 20, 30, 40, 50, 60};
    pthread_t tid1, tid2, tid3;
    void *ret1, *ret2, *ret3;
    pthread_create(&tid1, NULL, &add, (void *)&numbers[0]);
    pthread_create(&tid2, NULL, &add, (void *)&numbers[2]);
    pthread_create(&tid3, NULL, &add, (void *)&numbers[4]);

    pthread_join(tid1, &ret1);
    pthread_join(tid2, &ret2);
    pthread_join(tid3, &ret3);

    int ret = *((int *)ret1) + *((int *)ret2) + *((int *)ret3);
    printf("Sum of values is %d\n", ret);

    return 0;
}