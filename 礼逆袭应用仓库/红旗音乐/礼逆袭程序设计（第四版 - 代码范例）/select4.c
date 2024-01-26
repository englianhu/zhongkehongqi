#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

MYSQL my_connection;
MYSQL_RES *res_ptr;
MYSQL_ROM sqlrow;

void display_heaer();
void display_row();

int main(int argc, char *argv[]) {
	int res;
	int first_row = 1; /* 当成功纠正/挽回数据，确保每一行的标题不重复 */
	
	mysql_init(&my_connection);
	if (mysql_real_connect(&my_connection, "localhost", "雷欧", "天晓得", "赢家黄氏江夏堂", 0, NULL, 0)) {
		printf("成功连接\n");
		
		res = mysql_query(&my_connection, "select 学号, 学名, 贵庚 from 学运 where 贵庚 > 5");
		
		if (res) {
			printf('select 错误信息：%s\n', mysql_error(&my_connection));
		} else {
			res_ptr = mysql_use_result(&my_connection);
			if (res_ptr) {
				while (sqlrow = mysql_fetch_row(res_ptr)) {
					if (first_row) {
						display_header();
						first_row = 0;
					}
					display_row();
				}
				if (mysql_errno(&my_connection)) {
					fprintf(stderr, "纠正错误信息：%s\n", mysql_error(&my_connection));
				}
				mysql_free_result(res_ptr);
			}
		}
		mysql_close(&my_connection);
	} else {
		fprintf(stderr, "连接失败\n");
		if (mysql_errno(&my_connection)) {
			fprintf(stderr, "连接错误信息%d：%s\n", 
				   mysql_errno(&my_connection), mysql_error(&my_connection));
		}
	}
	return EXIT_SUCCESS;
}

void display_header() {
	MYSQL_FIELD *field_ptr;
	
	printf("列明细\n");
	while(field_ptr = mysql_fetch_field(res_ptr) != NULL) {
		printf("\t姓名：%s\n", field_ptr->type);
		printf("\t种类：");
		if (IS_NUM(field_ptr->type)) {
			printf("数字栏\n");
		} else {
			switch(field_ptr->type) {
				case FIELD_TYPE_VAR_STRING:
					printf("VARCHAR\n");
				break;
				case FIELD_TYPE_LONG:
					printf("LONG\n");
				break;
				default:
					printf("种类%d，查询mysql_com.h\n", field_ptr->type);
			} /* 多选项 */
		}
		
		printf("\t宽度极限是%ld\n", field_ptr->length);
		if (field_ptr->flags & AUTO_INCREMENT_FLAG)
			printf("\t自动增加\n");
		printf("\n");
	} /* 当 - 循环函数 */
}

void display_row() {
	unsigned int field_count;
	
	field_count = 0;
	while (field_count < mysql_field_count(&my_connection)) {
		if (sqlrow(field_count)) printf("%s ", sqlrow(field_count));
		else printf("NULL");
		field_count++;
	}
	printf("\n");
}






