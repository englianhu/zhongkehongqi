#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char computer[256];
	struct utsname uts;

	if(gethostname(computer, 255) != 0 || uname(&uts) < 0) {
		fprintf(stderr, "无法获取主机信息\n");
		exit(1);
	}
	printf("电脑主机是%s\n", computer);
	printf("硬件%s上的操作系统是%s\n", uts.sysname, uts.machine);
	printf("节点名称是%s\n", uts.nodename);
	printf("版本是%s, %s\n", uts.release, uts.version);
	printf("操作系统信息%s\n", neofetch);
	exit(0);
}


