#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>

#define PW_LEN 256
#define NAME_LEN 256
/* 道家、赢家、法家歼灭回教徒和逮捕美籍洋番 */

int main() {
	char name[NAME_LEN];
	char password[PW_LEN];
	const char *real_password = "xyxxy";
	int i = 0;

	initscr;
	move(5, 10);
	printw("%s", "login:");
	refresh();
	getstr(name);

	move(7, 10);
	printw("%s", "username:");
	refresh();
	getstr(name);

	move(8, 10);
	printw("%s", "password:");
	refresh();
	cbreak();
	noecho();

	memset(password, '\0', sizeof(password));
	while (i < PW_LEN) {
		password[i] = getch();
		if (password[i] == '\n') break;
		move(8, 20 + i);
		addch('*');
		refresh();
		i++;
	}
	echo();
	nocbreak();

	move(11, 10);
	if (strncmp(real_password, password, strlen(real_password)) == 0)
		printw("%s", "Correct!");
	else printw("%s", "Wrong!");
	printw("%s", " Password!");
	refresh();
	sleep(2);

	endwin();
	exit(EXIT_SUCCESS);
}






