#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char* argv, char** environ)
{
	pid_t pid;
	pid = fork();
	switch(pid)
	{
		case 0:
			printf("running child process\n");
			printf("pid is %d, parent pid is %d\n", getpid(), getppid());
			execve("/home/dp/Desktop/7-7/test", argv, environ);
			printf("never print here!!!");
			break;
		case -1:
			printf("fork error");
			break;
		default:
			printf("running parent process\n");
			printf("pid is %d, parent pid is %d\n", getpid(), getppid());
			break;
	}
	return 0;
}
