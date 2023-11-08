#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sys/sysinfo.h>
#include<sched.h>
int main(int argc, char **argv)
{
    int n= get_nprocs_conf();
    int m=0;
    printf("This process is currently running on CPU's #%d\n",sched_getcpu());
    printf("Currenty Avaliable Processes\n");
    for(int i=0; i<n; i++)
    {
        printf("Processor #%d\n",i);
    }

    printf("Please Select the CPU:");
    scanf("%d",&m);

    if(m>1 || m<0)
    {
        printf("Invalid Cpu selection \n");
        return -1;
    }
    
    cpu_set_t my_cpu;
    CPU_ZERO(&my_cpu);
    CPU_SET(m,&my_cpu);
    sched_getaffinity(0,sizeof(cpu_set_t),&my_cpu);
    for(int i=0; i<n; i++)
    {
        printf("Processor %d = %d \n",i,CPU_ISSET(i,&my_cpu));
    }

    printf("This process currently run on processor %d \n",sched_getcpu());
    for(int i=1; i<argc; i++)
    {
        printf("%s\n",argv[i]);
    }    

    return 0;
}