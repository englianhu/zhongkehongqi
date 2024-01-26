#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

int main()
{
	setupterm("查无此人", fileno(stdout), (int *)0);
	printf("查询完毕。\n");
	exit(0);
}






