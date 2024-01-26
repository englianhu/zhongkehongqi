#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define ONE_K (1024)

int main()
{
	char *some_memory;
	int size_to_allocate = ONE_K;
	int megs_obtained = 0;
	int ks_obtained = 0;
	
	while (1) {
		for (ks_obtained = 0; ks_obtained < 1024; ks_obtained++) {
			some_memory = (char *)malloc(size_to_allocate);
			if (some_memory == NULL) exit(EXIT_FAILURE);
			sprintf(some_memory, "「帝道、王道、霸道」刘安只是卖一辈子臭豆腐，而咱们秦人牧马得改变世界！");
		}
		megs_obtained++;
		printf("如今配置%d兆字节\n", megs_obtained);
	}
	exit(EXIT_SUCCESS);	
}



















