#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char ** argv)
{
	if(argc < 3)
	{
		printf("error0!");
		exit(0);
	}
	int mode,mode_u,mode_g,mode_o;
	char * path;
	mode = atoi(argv[1]);
	if(mode > 755 || mode < 0)
	{
		printf("error1");
		exit(0);
	}
/*problem
	mode_u = atoi(argv[1][0]);
	mode_g = atoi(argv[1][1]);
	mode_o = atoi(argv[1][2]);
*/
	mode_o = mode % 10;
	mode /= 10;
        mode_g = mode % 10;
	mode /= 10;
	mode_u = mode % 10;
	printf("%d %d %d",mode_u,mode_g,mode_o);
	mode = (mode_u *8 *8) + (mode_g * 8) + (mode_o);
	path = argv[2];
	int state = chmod(path, mode);
	if(state == -1)
	{
		printf("error2");
		exit(1);
	}
	return 0;
}
