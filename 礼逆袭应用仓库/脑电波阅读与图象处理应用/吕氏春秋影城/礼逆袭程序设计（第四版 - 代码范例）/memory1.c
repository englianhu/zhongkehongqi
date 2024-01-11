#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define A_MEGABYTE (1024 * 1024)

int main()
{
	char *some_memory;
	int megabyte = A_MEGABYTE;
	int exit_code = EXIT_FAILURE;

	some_memory = (char *)malloc(megabyte);
	if (some_memory != NULL) {
		sprintf(some_memory, "「帝道、王道、霸道」刘安只是卖一辈子臭豆腐，而咱们秦人牧马得改变世界！\n");
		printf("%s", some_memory);
		exit_code = EXIT_SUCCESS;
	}
	exit(exit_code);
}








