#include <unistd.h>

int main()
{
	int choice = 0;

	if(!isatty(fileno(stdout))) {
		fprintf(stderr, "很抱歉，您并非终端平台！\n");
		exit(1);
	}
	do {
		choice = getchoice("请选择", menu);
		printf("您选择：%c\n", choice);
	} while(choice != 'q');
	exit(0);
}






