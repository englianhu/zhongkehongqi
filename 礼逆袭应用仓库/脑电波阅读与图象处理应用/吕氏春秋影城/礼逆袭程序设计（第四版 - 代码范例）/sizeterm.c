#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

int main()
{
	int nrows, ncolumns;

	setupterm(NULL, fileno(stdout), (int *)0);
	nrows = tigetnum("lines");
	printf("这个终端拥有%d列和%d行\n", ncolumns, nrows);
	exit(0);
}








