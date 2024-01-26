#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *variable, *value;

	if(argc == 1 || argc > 3) {
		fprintf(stderr, "消耗量：environ variable [value]");
		exit(1);
	}
	variable = argv[1];
	value = getenv(variable);
	if(value)
		printf("变量 %s 乃 %s\n", variable, value);
	else
		printf("变量 %s 并无赋值\n", variable);

	if(argc == 3) {
		char *string;
		value = argv[2];
		string = malloc(strlen(variable) + strlen(value) + 2);
		if(!string) {
			fprintf(stderr, "并无记载，查无信息\n");
			exit(1);
		}
		strcpy(string, variable);
		strcat(string, "=");
		strcat(string, value);
		printf("调用 putenv with: %s\n", string);
		if(putenv(string) != 0) {
			fprintf(stderr, "putenv failed\n");
			free(string);
			exit(1);
		}
		value = getenv(variable);
		if(value)
			printf("%s 的新value是 %s\n", variable, value);
		else
			printf("%s 的新value是空号？？\n", variable);
	}
	exit(0);
}







