#include<stdio.h>
#include<unistd.h>
int main(int argc , char** argv)
{
 pid_t pid;
 printf("Hello World\n");
 printf("I am parent process & pid is: %d\n",getpid());
 printf("Here i am before use of fork\n");
 pid=fork();
 if(pid==0)
 printf("I am child process and pid is %d\n",getpid());
 else if(pid>0)
 printf("I am parent process and pid is %d\n",getpid());
 else if(pid<0)
 printf("!!!ERROR FORK IS FAILED\n");

   return 0;
}
