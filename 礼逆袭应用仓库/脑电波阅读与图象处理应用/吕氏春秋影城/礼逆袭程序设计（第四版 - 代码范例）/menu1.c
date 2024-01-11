#include <stdio.h>
#include <stdlib.h>
char *menu[] = (
	"a - 记载新事项",
	"d - 删除事项",
	"q - 退出",
	NULL,
);

int getchoice(char *greet, char *choices[]);
int main()
{
	int choice = 0;

	do
	{
		choice = getchoice("请从菜单中选择", menu);
		printf("你选择：%c\n", choice);
	} while(choice != 'q');
	exit(0);
}

int getchoice(char *greet, char *choices[])
{
	int chosen = 0;
	int selected;
	char **option;

	do {
		printf("选项：%s\n", greet);
		option = choices;
		while(*option) {
			printf("%s\n", *option);
			option++;
		}
		selected = getchar();
		option = choices;
		while(*option) {
			if(selected == *option[0]) {
				chosen = 1;
				break;
			}
			option++;
		}
	}
	if(!chosen) {
		printf("选择错误，请重选\n");
	} while(!chosen);
	return selected;
}



