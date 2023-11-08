#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sched.h>
#include<sys/sysinfo.h>
int main()
{
    printf("Number of Processes Configured by system is %d \n",get_nprocs_conf());
    printf("Number of Processes currentyl avaliable in system is %d \n", get_nprocs());
    printf("Process currently schedule on # %d cpu \n",sched_getcpu());

    return 0;
}