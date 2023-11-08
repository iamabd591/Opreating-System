#define _GNU_SOURCE
#include<sched.h>
#include<stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>
int main()
{
cpu_set_t my_set;  /* Define your cpu_set bit mask. */
CPU_ZERO(&my_set);/* Initialize it all to 0, i.e. no CPUs selected. */
sched_getaffinity(0, sizeof(cpu_set_t), &my_set); 
/* Get affinity of this process to 
/* the defined mask*/
int nproc = get_nprocs_conf();
for (int i = 0; i < nproc; i++)
 printf("Processor# %d = %d \n", i,CPU_ISSET(i, &my_set)); /* check one by one if the affinity of processor is in the mask*/
return 0;
}
