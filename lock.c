#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int set_lock(int fd, struct flock * lock)
{
	if(fcntl(fd, F_SETLK, lock) == 0)
	{
		if(lock->l_type == F_RDLCK)
			printf("set read lock, pid is %d\n",getpid());
		else if(lock->l_type == F_WRLCK)
			printf("set write lock, pid is %d\n",getpid());
		else if(lock->l_type == F_UNLCK)
			printf("unlock\n");
	}
	else
		printf("set error\n");
	return 0;
}

int get_lock(int fd, struct flock * test_lock)
{
	if(fcntl(fd, F_GETLK, test_lock) == 0)
	{
		if(test_lock->l_type == F_RDLCK)
		{
			printf("set fail for read lock\n");
			return 1;
		}	
		else if(test_lock->l_type == F_WRLCK)
		{
			printf("set fail for write lock\n");
			return 2;
		}
		else if(test_lock->l_type == F_UNLCK)
		{
			printf("you can set new lock\n");	
			return 0;
		}
	}
	else
		printf("get lock fail\n");
}

int main()
{
	int fd, len, ret;
	char write_buf[32] = "hello";
	char read_buf[32];
	struct flock lock;
	memset(&lock, 0, sizeof(struct flock));
	lock.l_start = SEEK_SET;
	lock.l_whence = 0;
	lock.l_len = 0;
	
	if((fd = open("test", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU )) == -1)
		printf("open error\n");
	if(write(fd, write_buf, strlen(write_buf)) != strlen(write_buf))
		printf("write error\n");
	if(get_lock(fd, &lock) == 0)
	{
		lock.l_type = F_RDLCK;
		set_lock(fd, &lock);
	}

	getchar();
	if((len = lseek(fd, 0, SEEK_CUR)) == -1)
		printf("lseek error\n");
	else
		printf("lseek success,lenth is %d\n", len);
	
	lseek(fd, 0, SEEK_SET);
	if((ret = read(fd, read_buf, len)) < 0)
		printf("read error\n");
	else
	{
		read_buf[ret] = '\0';
		printf("%s\n",read_buf);
	}
	if(get_lock(fd, &lock) == 0)
	{
		lock.l_type = F_WRLCK;
		set_lock(fd, &lock);
	}
	
	lock.l_type = F_UNLCK;
	set_lock(fd, &lock);
	close(fd);

	return 0;
}
