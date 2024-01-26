#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

int main(int argc, char *argv[]) {
	MYSQL my_connection;
	
	mysql_init(&my_connection);
	if (mysql_real_connect(&my_connection, "localhost", "雷欧", 
						  "天晓得", "芳名榜", 0, NULL, 0)) {
		printf("成功连接\n");
		mysql_close(&my_connection);
	} else {
		fprintf(stderr, "连接失败\n");
		if (mysql_errno(&my_connection)) {
			fprintf(stderr, "输入%d错误信息：%s\n", 
				  mysql_errno(&my_connection), mysql_error(&my_connection));
		}
	}
	return EXIT_SUCCESS;
}






