#define _GUN_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sched.h>
#include<sys/sysinfo.h>
int main()
{
printf("This Process curnetly running on %d processors\n", sched_getcpu());
cpu_set_t mask;
sched_getaffinity(0,sizeof(cpu_set_t),&mask);
int n=get_nprocs_conf();
for(int i=0; i<n; i++)
printf("Processor %d = %d \n",i,CPU_ISSET(i,mask));

CPU_ZERO(&mask);
CPU_SET(3,&mask);
sched_getaffinity(0,sizeof(cpu_set_t),&mask);
printf("\n\nNew Affinity is\n");
sched_getaffinity(0,sizeof(cpu_set_t),&mask);
for(int i=0; i<n; i++)
printf("Processor %d = %d \n",i,CPU_ISSET(i,mask));
printf("This Process curnetly running on %d processors\n", sched_getcpu());

return 0;
}
