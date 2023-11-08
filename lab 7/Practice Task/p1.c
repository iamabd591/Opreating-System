#include<sys/sysinfo.h>
#include<stdio.h>
int main()
{
printf("This system has %d processors configured and %d processors available.\n ",get_nprocs_conf(), get_nprocs());
return 0;
}
