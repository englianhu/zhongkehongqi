#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char *some_memory = (char *)0;
	
	printf("读取无效的空号%s\n", some_memory);
	sprintf(some_memory, "记载无效的空号\n");
	exit(EXIT_SUCCESS);
}












