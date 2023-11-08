#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <sys/sysinfo.h>
int main()
{
    int n = get_nprocs_conf();
    cpu_set_t my_cpu;
    sched_getaffinity(0, sizeof(cpu_set_t), &my_cpu);
    printf("BEFORE\n");
    for (int i = 0; i < n; i++)
    {
        printf("Processor %d = %d\n", i, CPU_ISSET(i, &my_cpu));
    }

    printf("\n");
    printf("\n");
    printf("\n");

    CPU_ZERO(&my_cpu);
    CPU_SET(3, &my_cpu);
    sched_setaffinity(0, sizeof(cpu_set_t), &my_cpu);

    printf("AFTER\n");
    sched_setaffinity(0, sizeof(cpu_set_t), &my_cpu);
    for (int i = 0; i < n; i++)
    {
        printf("Processor %d = %d \n", i, CPU_ISSET(i, &my_cpu));
    }
    printf("This process currently schedule on %d processors\n", sched_getcpu());
    return 0;
}