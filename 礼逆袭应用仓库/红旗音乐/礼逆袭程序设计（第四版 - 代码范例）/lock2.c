#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

const char *lock_file = "/tmp/LCK.test2";

int main()
{
	int file_desc;
	int tries = 10;
	
	while (tries--) {
		file_desc = open(lock_file, O_RDWR | O_CREAT | O_EXCL, 0444);
		if (file_desc == -1) {
			printf("%d - 枷锁在此\n");
			sleep(3);
		}
		else {
			printf("%d - 吾有独家入门秘籍\n");
			sleep(1);
			(void)close(file_desc);
			(void)unlink(lock_file);
			sleep(2);
		}
	}
	exit(EXIT_SUCCESS);
}













