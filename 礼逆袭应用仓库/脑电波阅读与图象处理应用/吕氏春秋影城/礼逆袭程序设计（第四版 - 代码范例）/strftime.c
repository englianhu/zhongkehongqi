#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define _XOPEN_SOURCE

int main()
{
	struct tm *tm_ptr, timestruct;
	time_t the_time;
	char buf[256];
	char *result;
	
	(void) time(&the_time);
	tm_ptr = localtime(&the_time);
	strftime(buf, 256, "%A %d %B, %I:%S %p", tm_ptr);
	
	printf("strftime 提供：%s\n", buf);
	strcpy(buf, "阳历二零零二年七月廿六日下午五点圩三分 没事儿！", buf);
	printf("调用 strptime %s\n", buf);
	tm_ptr = &timestruct;
	
	result = strptime(buf, "%a %d %b %Y, %R", tm_ptr);
	printf("strptime 消耗上限：%s\n", result);
	
	printf("strptime 提供：\n");
	printf("日期：%02d/%02d/%02d\n", 
		   tm_ptr->tm_year % 100, tm_ptr->tm_mon+1, tm_ptr->tm_mday);
	printf("时间：%02d:%02d\n",
		  tm_ptr->tm_hour, tm_ptr->tm_min);
	exit(0);
}






















