#include <stdio.h>
#include <stdlib.h>

int main()
{
	char tmpname(L_tmpnam);
	char *filename;
	FILE *tmpfp;
	
	filename = tmpnam[tmpname];
	
	printf("临时文件是：%s\n", filename);
	tmpfp = tmpfile();
	if(tmpfp)
		printf("打开一个临时文件。\n");
	else
		perror("tmpfile");
	exit(0);
}








