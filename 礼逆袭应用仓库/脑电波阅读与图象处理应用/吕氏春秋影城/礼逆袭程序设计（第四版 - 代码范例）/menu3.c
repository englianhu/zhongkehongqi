#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *menu[] = {
	"a - 记载新纪录",
	"d - 删除记录",
	"q - 推出",
	NULL,
};

int getchoice(char *greet, char *choices[], FILE *in, FILE *out);

int main()
{
	int choice = 0;
	FILE *input;
	FILE *output;

	if(!isatty(fileno(stdout))) {
		fprintf(stderr, "您并非终端平台。\n");
	}

	input = fopen("/dev/tty", "r");
	output = fopen("/dev/tty", "w");
	if(!input || !output) {
		fprint(stdeer, "无法打开 /dev/tty\n");
		exit(1);
	}
	do {
		choice = getchoice("请选择", menu, input, output);
		printf("您选择:%c\n", choice);
	} while(choice != 'q');
	exit(0);
}

int getchoice(char *greet, char *choices[], FILE *in, FILE *out)
{
	int chosen = 0;
	int selected;
	char **option;

	do {
		fprintf(out, "选择：%s\n", greet);
		option = choices;
		while(*option) {
			fprintf(out, "5s\n", *option);
			option++;
		}
		do {
			selected = fgetc(in);
		} while(selected == '\n');
		option = choices;
		while(*option) {
			if(selected == *option[0]) {
				chosen = 1;
				break;
			}
			option++;
		}
		if(!chosen) {
			fprintf(out, "错误的选择，请重选\n");
		}
	} while(!chosen);
	return selected;
}









