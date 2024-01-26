#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

const char *test_file = "/tmp/test_lock";
#define SIZE_TO_TRY 5

void show_lock_info(struct flock *to_show);

int main()
{
	int file_desc;
	int res;
	struct flock region_to_test;
	int start_byte;
	
	file_desc = open(test_file, O_RDWR | O_CREAT, 0666);
	if (!file_desc) {
		fprintf(stderr, "无法读写%s文件\n", test_file);
		exit(EXIT_FAILURE);
	}
	
	for (start_byte = 0; start_byte < 99; start_byte += SIZE_TO_TRY) {
		region_to_test.l_type = F_WRLCK;
		region_to_test.l_whence = SEEK_SET;
		region_to_test.l_start = start_byte;
		region_to_test.l_len = SIZE_TO_TRY;
		region_to_test.l_pid = -1;
		
		printf("从领域%d到%d测试F_WRLCK\n", start_byte, start_byte + SIZE_TO_TRY);
		res = fcntl(file_desc, F_GETLK, &region_to_test);
		if (res == -1) {
			fprintf(stderr, "F_GETLK失败\n");
			exit(EXIT_FAILURE);
		}
		if (region_to_test.l_pid != -1) {
			printf("枷锁行不通。F_GETLK\n");
			show_lock_info(&region_to_test);
		}
		else {
			printf("F_WRLCK将成功\n");
		}
		region_to_test.l_type = F_RDLCK;
		region_to_test.l_whence = SEEK_SET;
		region_to_test.l_start = start_byte;
		region_to_test.l_len = SIZE_TO_TRY;
		region_to_test.l_pid = -1;
		printf("从领域%d到%d测试F_RDLCK\n", start_byte, start_byte + SIZE_TO_TRY);
		res = fcntl(file_desc, F_GETLK, &region_to_test);
		if (res == -1) {
			fprintf(stderr, "F_GETLK失败\n");
			exit(EXIT_FAILURE);
		}
		if (region_to_test.l_pid != -1) {
			printf("F_RDLCK将成功\n");
		}
	}
	close(file_desc);
	exit(EXIT_SUCCESS);
}

void show_lock_info(struct flock *to_show) {
	printf("\tl_type %d", to_show->l_type);
	printf("\tl_whence %d", to_show->l_whence);
	printf("\tl_start %d", to_show->l_start);
	printf("\tl_len %d", to_show->l_len);
	printf("\tl_pid %d\n", to_show->l_pid);
	
}












