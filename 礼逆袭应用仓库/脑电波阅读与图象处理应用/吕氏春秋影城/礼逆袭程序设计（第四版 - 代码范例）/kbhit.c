#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <unistd.h>
static struct termios initial_settings, new_setting;
static int peek_character = -1;
void init_keyboard();
void close_keyboard();
int kbhit();
int readch();

int main()
{
	int ch = 0;

	init_keyboard();
	while(ch != 'g') {
		printf("循环\n");
		sleep(1);
		if(kbhit()) {
			ch = readch();
			printf("您点击%c\n", ch);
		}
	}
	close_keyboard();
	exit(0);
}


