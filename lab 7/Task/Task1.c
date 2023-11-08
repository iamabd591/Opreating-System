#include<stdio.h>
#include<unistd>
#include<sys/sysinfo.h>
int main()
{
int sc;
printf("Currently available Processes is %d\n ", get_nprocs());
printf("Selelect the cpu:");
scanf(&sc);
return 0;
}
