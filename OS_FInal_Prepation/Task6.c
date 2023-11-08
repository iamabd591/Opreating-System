#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <sys/sysinfo.h>
int main(int argc, char **argv)
{
    float sum = 0;
    float avg = 0;
    int min = 0;
    int max = 0;
    int temp = 0;
    if (argc < 2)
    {
        printf("Too Few Arguments\n");
        return -1;
    }
    int *arr = (int *)mallco((argc - 1) * sizeof(int));
    for (int i = 1; i < argc; i++)
    {
        arr[i] = atoi(argv[i + 1]);
    }

    cpu_set_t mycpu;
    CPU_ZERO(&mycpu);
    pid_t pid = fork();

    if (pid == 0)
    {
        CPU_SET(2, &mycpu);
        sched_getaffinity(0, sizeof(cpu_set_t), &mycpu);
        printf("This process currently running on cpu %d\n", sched_getcpu());
        for (int i = 1; i < argc; i++)
        {
            sum +=arr[i];
        }
        avg = sum / argc - 1;
        printf("Average is %f\n", avg);
    }
    else if (pid < 0)
        return -1;

    cpu_set_t mycpu;
    CPU_ZERO(&mycpu);
    pid = fork();

    if (pid == 0)
    {
        CPU_SET(3, &mycpu);
        sched_getaffinity(0, sizeof(cpu_set_t), &mycpu);
        printf("This process currently running on cpu %d\n", sched_getcpu());
        max, min = arr[1];
        for (int i = 1; i < argc; i++)
        {
            if (min > arr[i])
            {
                min = arr[i];
            }
            if (max < arr[i])
            {
                max = arr[i];
            }
        }

        printf("Minimum Maximum respectively is %d %d \n", min, max);
    }
    else if (pid < 0)
        return -1;

    cpu_set_t mycpu;
    CPU_ZERO(&mycpu);
    pid = fork();

    if (pid == 0)
    {
        CPU_SET(4, &mycpu);
        sched_getaffinity(0, sizeof(cpu_set_t), &mycpu);
        printf("This process currently running on cpu %d\n", sched_getcpu());
        for (int i = 1; i < argc; i++)
        {
            for (int j = 1; j < argc; j++)
            {
                if (arr[i] < arr[j])
                {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }

        for (int i = 1; i < argc; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    else if (pid < 0)
        return -1;
    waitpid(pid, NULL, 0);
    return 0;
}