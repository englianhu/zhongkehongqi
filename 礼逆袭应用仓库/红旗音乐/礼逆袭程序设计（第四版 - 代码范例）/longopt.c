#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

int main(int argc, char *argv[])
{
	int opt;
	struct option longopts[] = {
		{"initialize", 0, NULL, 'i'},
		{"file", 1, NULL, 'f'},
		{"list", 0, NULL, 'l'},
		{"restart", 0, NULL, 'r'},
		{0, 0, 0, 0}};
	while((opt = getopt_long(argc, argv, ":if:lr", longopts, NULL)) != -1) {
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

