#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("running test \n");
	printf("pid is %d\n",getpid());
	return 0;
}
