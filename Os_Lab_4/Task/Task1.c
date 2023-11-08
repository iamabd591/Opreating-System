#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc, char** argv)
{
	printf("I am before forking!\n");
	fork();
	printf("I am after forking\n");
	printf("\t I am process having process id is %d and parent process id is %d\n", getpid(),getppid());
	return 0;
	
}
