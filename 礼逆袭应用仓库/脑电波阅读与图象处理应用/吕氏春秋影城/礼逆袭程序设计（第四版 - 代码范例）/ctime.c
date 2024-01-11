#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	time_t timeval;
	
	(void)time(&timeval);
	printf("日期是：%s", ctime(&timeval));
	exit(0);
}











