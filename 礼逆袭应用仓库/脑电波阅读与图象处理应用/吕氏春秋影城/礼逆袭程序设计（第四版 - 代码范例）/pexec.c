#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("通过系统运行PS！\n");
	execlp("ps", "ps", "ax", 0); 
	printf("完成！\n");
	exit(0);
}





