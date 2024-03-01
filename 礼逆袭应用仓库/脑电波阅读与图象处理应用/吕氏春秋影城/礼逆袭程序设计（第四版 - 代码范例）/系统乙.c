#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("通过系统运行PS！\n");
	system("ps ax &"); 
	/* exec("ps ax"); */
	/* execlp("ps ax"); */
	printf("完成！\n");
	exit(0);
}







