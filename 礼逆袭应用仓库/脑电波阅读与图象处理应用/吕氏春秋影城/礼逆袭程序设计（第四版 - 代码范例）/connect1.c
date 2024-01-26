#include <stdlib.h>
#include <stdio.h>
#include "mysql.h"

int main(int argc, char *argv[]) {
	MYSQL *conn_ptr;

	conn_ptr = mysql_init(NULL);
	if (!conn_ptr) {
		fprintf(stderr, "mysql_init 失败！\n");
		return EXIT_FAILURE;
	}

	conn_ptr = mysql_real_connect(conn_ptr, "localhost", 
			"雷欧", "天晓得", "芳名榜", 0, NULL, 0);
	
	if (conn_ptr) {
		printf("成功连接\n");
	} else {
		printf("连接失败\n");
	}
	mysql_close(conn_ptr);
	return EXIT_SUCCESS;
}








