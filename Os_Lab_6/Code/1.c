#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include <fcntl.h>
#include<stdlib.h>
#define READ 0
#define WRITE 1

int main(int argc, char** argv)
{
int pid ,fd[2];
if(pipe(fd)==-1)
{
perror("Pippe Creation is failed");
exit(-1);
}

pid=fork();
if (pid==-1)
{
    printf("Fork Creation is Faild\n");
    exit(1);
}
else if(pid==0)
{
    close(fd[WRITE]);
    dup2(fd[READ],0);
    close(fd[READ]);
    execlp ( argv[2], argv[2], NULL) ; 
}
else
{
    //wait(NULL);
    close(fd[READ]);
    dup2(fd[WRITE],1);
    close(fd[WRITE]);
    execlp ( argv[1], argv[1], NULL) ; 
}
return 0;
}




