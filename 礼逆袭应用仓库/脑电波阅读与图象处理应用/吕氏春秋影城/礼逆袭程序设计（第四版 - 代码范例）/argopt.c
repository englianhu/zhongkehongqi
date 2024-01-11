#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int opt;

	while((opt = getopt(argc, argv, ":if:lr")) != -1) {
		switch(opt) {
			case 'i':
			case 'l':
			case 'r':
				printf("选项：%c\n", opt);
				break;
			case 'f':
				printf("文件名：%s\n", optarg);
				break;
			case ':':
				printf("选项需要赋值\n");
				break;
			case '?':
				printf("未知选项：%c\n", optopt);
				break;
		}
	}
	for(; optind < argc; optind++)
		printf("参数：%s\n", argv[optind]);
	exit(0);
}








