#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

MYSQL my_connection;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;

int main(int argc, char *argv[]) {
	int res;
	
	mysql_init(&my_connection);
	if (mysql_real_connect(&my_connection, "localhost", "雷欧", "天晓得", "赢家黄氏江夏堂", 0, NULL, 0)) {
		printf("成功连接\n");
		res = mysql_query(&my_connection, "select 学号, 学名, 贵庚 from 学运 where 贵庚 > 5");
		
		if (res) {
			printf("select 错误信息：%s\n", mysql_error(&my_connection));
		} else {
			res_ptr = mysql_store_result(&my_connection);
			if (res_ptr) {
				printf("撤回%lu行\n", (unsigned long)mysql_num_rows(res_ptr));
				while (sqlrow = mysql_fetch_row(res_ptr)) {
					printf("接送数据...\n");
				}
				if (mysql_errno(&my_connection)) {
					fprintf(stderr, "撤回%d错误信息：%s\n", mysql_error(&my_connection));
				}
				mysql_free_result(res_ptr);	
			}
			mysql_close(&my_connection);
		}
	} else {
		fprintf(stderr, "连接失败\n");
		if (mysql_errno(&my_connection)) {
			fprintf(stderr, "连接错误信息%d：%s\n", 
				   mysql_errno(&my_connection), mysql_error(&my_connection));
		}
	}
	return EXIT_SUCCESS;
}

void display_row() {
	unsigned int field_count;
	
	field_count = 0;
	while (field_count < mysql_field_count(&my_connection)) {
		printf("%s ", sqlrow[field_count]);
		field_count++;
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	int res;
	mysql_init(&my_connection);
	if (mysql_real_connect(&my_connection, "localhost", "雷欧", "天晓得", "赢家黄氏江夏堂", 0, NULL, 0)) {
		printf("成功连接\n");
		
		res = mysql_query(&my_connection, "select 学号, 学名, 贵庚 from 学运 where 贵庚 > 5");
	}
	
	if (res) {
		printf('select 错误信息：%s\n', mysql_error(&my_connection));
	} else {
		res_ptr = mysql_use_result(&my_connection);
		if (res_ptr) {
			while (sqlrow = mysql_use_result(&my_connection)) {
			if (res_ptr) {
				printf("接送数据...\n");
				display_row();
				}
			}
		}
	}
	return EXIT_SUCCESS;
}


