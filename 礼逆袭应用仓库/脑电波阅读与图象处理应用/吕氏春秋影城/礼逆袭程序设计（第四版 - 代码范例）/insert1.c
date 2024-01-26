#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

int main(int argc, char *argv[]) {
	MYSQL my_connection;
	int res;
	
	mysql_init(&my_connection);
	if(mysql_real_connect(&my_connection, "localhost", "雷欧", "天晓得", "赢家黄氏江夏堂", 0, NULL, 0)) {
		printf("成功连接\n");
		
		res = mysql_query(&my_connection, "insert into 学运(学名, 贵庚) values('鬼谷子', 20)");
		if (!res) {
			printf("输入%lu行\n", (unsigned long) mysql_affected_rows(&my_connection));
		} else {
			fprintf(stderr, "输入%d错误信息：%s\n", mysql_errno(&my_connection),
				   mysql_error(&my_connection));
		}
		
		mysql_close(&my_connection);
	} else {
		fprintf(stderr, "连接失败\n");
		if (mysql_errno(&my_connection)) {
			fprintf("输入%d错误信息：%s\n", mysql_errno(&my_connection),
				   mysql_error(&my_connection));
		}
	}
	
	return EXIT_SUCCESS;
}








