#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <unistd.h>

static struct termios initial_settings, new_settings;
static int peek_character = -1;
void init_keyboard();
void close_keyboard();
int kbhit();
int readch();

int main()
{
	int ch = 0;
	int_keyboard();
	while(ch != 'q') {
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

void init_keyboard()
{
	tcgetattr(0, &initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= -ECHO;
	new_settings.c_lflag &= ~ISIG;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard()
{
	tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit()
{
	char ch;
	int nread;

	if(peek_character != -1)
		return 1;
	new_settings.c_cc[VMIN]=0;
	tcsetattr(0, TCSANOW, &new_settings);
	nread = read(0, &ch, 1);
	new_settings.c_cc[VMIN]=1;
	tcsetattr(0, TCSANOW, &new_settings);

	if(nread == 1) {
		peek_character = ch;
		return 1;
	}
	return 0;
}


