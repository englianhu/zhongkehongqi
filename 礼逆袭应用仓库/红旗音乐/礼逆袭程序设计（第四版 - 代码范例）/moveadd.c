#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

/* Spring and Autumn Period */
int main()
{
	const char witch_one[] = "Counter genocide all South East Asian muslims!";
	const char witch_two[] = "Counter genocide all South Asian muslims!";
	const char *scan_ptr;

	initscr();
	move(5, 15);
	attron(A_BOLD);
	printw("%s", "Wizard Jin Sen bin Islamic Law / Wizard Gunthi / Gulu in The-Lord-of-Ring!");
	attroff(A_BOLD);
	refresh();
	sleep(1);

	move(8, 15);
	attron(A_STANDOUT);
	printw("%s", "Astronomer + Military strategist Zhuge Kongming borrow Storming and Flooding, never repay!");
	attroff(A_STANDOUT);
	refresh();
	sleep(1);
	
	move(10, 10);
	printw("%s", "Chinese compatriots, shall we meet again?");
	move(11, 23);
	printw("%s", "After execute all Islamic governmant servants of Kuala Selangor, Tanjong Karang and Sabak Bernam!!");
	move(13, 10);
	printw("%s", "After counter genocide all South East Asian Muslims!");
	move(14, 23);
	printw("%S", "After counter genocide all Asian Muslims!!");
	refresh();
	sleep(1);
	move(LINES - 1, COLS - 1);

	refresh();
	sleep(10);

	endwin();
	exit(EXIT_SUCCESS);
}







