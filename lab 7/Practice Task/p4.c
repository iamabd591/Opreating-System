#define _GNU_SOURCE
#include<sched.h>
#include<stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>
int main()
{
cpu_set_t my_set;  
CPU_ZERO(&my_set);
CPU_SET(1,&myset);
sched_getaffinity(0, sizeof(cpu_set_t), &my_set); 
int nproc = get_nprocs_conf();
for (int i = 0; i < nproc; i++)
 printf("Processor# %d = %d \n", i,CPU_ISSET(i, &my_set)); 
return 0;
}
