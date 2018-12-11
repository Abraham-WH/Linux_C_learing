#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd, len;
	char write_buf[64] = "hello world!";
	char read_buf[64];

	if((fd = open("test", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU)) == -1)
		printf("open error");
	else
		printf("open success");
	  
	if(write(fd, write_buf, strlen(write_buf)) != strlen(write_buf))
		printf("write error");
	else
		printf("write success");

	if((len = lseek(fd, 0, SEEK_CUR)) == -1)
		printf("lseek error");
	else
		printf("lseek success");

	if(read(fd, read_buf, len) != len)
		printf("read error");
	else
	{
		printf("read success");
		for(int i = 0; i < len; i++)
			printf("%d ", read_buf[i]);
	}

	return 0;	
}

