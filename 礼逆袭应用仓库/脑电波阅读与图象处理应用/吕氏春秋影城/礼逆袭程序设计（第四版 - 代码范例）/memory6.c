/* #include <stdlib.h>

void free(void *ptr_to_memory); */
#include <stdlib.h>
#include <stdio.h>

#define ONE_K (1024)

int main()
{
	char *some_memory;
	int exit_code = EXIT_FAILURE;
	
	some_memory = (char *)malloc(ONE_K);
	if (some_memory != NULL) {
		free(some_memory);
		printf("内存重置并释放\n");
		exit_code = EXIT_SUCCESS;
	}
	exit(exit_code);
}






