#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	int file_desc;
	int save_errno;
	
	file_desc = open("/tmp/LCK.test", O_RDWR | O_CREAT | O_EXCL, 0444);
	if (file_desc == -1) {
		save_errno = errno;
		printf("无法打开加锁文件，错误信息%d\n", save_errno);
	}
	else {
		printf("成功打开加锁文件");
	}
	exit(EXIT_SUCCESS);
}












