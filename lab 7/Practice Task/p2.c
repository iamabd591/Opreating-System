#include<sched.h>
#include<stdio.h>
int main()
{
printf("This process is currently executing on processor# = %d ", sched_getcpu());

return 0;
}
