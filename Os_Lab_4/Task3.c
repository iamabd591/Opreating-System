#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(int argc , char* argv[])
{
 pid_t pid;
 int status=0;
 printf("Hello World\n");
 pid=fork();
 if(pid<0)
 perror("bad fork");
 else if(pid>0)
 printf("I am parent process and pid is %d\n",getpid());
 else if(pid<0)
 printf("!!!ERROR FORK IS FAILED\n");

   return 0;
}
