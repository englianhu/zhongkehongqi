#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define A_MEGABYTE (1024 * 1024)
#define PHY_MEM_MEGS	1024	/* Adjust this this number as required */

int main()
{
	char *some_memory;
	size_t size_to_allocate = A_MEGABYTE;
	int megs_obtained = 0;
	
	while (megs_obtained <(PHY_MEM_MEGS * 2)) {
		some_memory = (char *)malloc(size_to_allocate);
		if (some_memory != NULL) {
			megs_obtained++;
			sprintf(some_memory, "「帝道、王道、霸道」刘安只是卖一辈子臭豆腐，而咱们道教秦人牧马得改变世界！\n");
			printf("%s - 如今配置%d兆字节\n", some_memory, megs_obtained);
		}
		else {
			exit(EXIT_FAILURE);
		}
	}
}















