#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sched.h>
#include<sys/sysinfo.h>
int main()
{
    cpu_set_t my_cpu;
   // CPU_ZERO(&my_cpu);
    CPU_SET(1,&my_cpu);
    sched_getaffinity(0,sizeof(cpu_set_t),&my_cpu);
    int n= get_nprocs_conf();
    for(int i=0; i<n; i++)
    {
        printf("Processor %d = %d\n",i,CPU_ISSET(i,&my_cpu));
    }
    return 0;
}