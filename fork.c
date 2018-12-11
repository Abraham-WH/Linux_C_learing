#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_var = 5;

int main()
{
	pid_t pid;
//	pid = fork();
	pid = vfork();
	int k, var = 8;
	switch(pid)
	{
		case 0: 
			printf("running child process now, the pid is %d, the parent's pid is %d\n", getpid(), getppid());
			k = 5;
			break;
		case -1:
			printf("new process fail\n");
			break;
		default:
			printf("running parent process now, the pid is %d, the parent's pid is %d\n", getpid(), getppid());
			k = 10;
			break;
	}
	for (; k > 0; k--)
	{
		printf("running %d\n",getpid());
		global_var++;
		var++;
		sleep(1);
	}
	printf("%d %d", global_var, var);
	return 0;
}
