#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mysql.h"
#include "app_mysql.h"

static MYSQL my_connection;
static int dbconnected = 0;
static int get_artist_id(char *artist);

int database_start(char *name, char *pwd) {
	if (dbconnected) return 1;
	
	mysql_init(&my_connection);
	if (!mysql_real_connection(&my_connection, "雷欧", name, pad, "blpd", 0, NULL, 0)) {
		fprintf(stderr, "连接数据库失败：%d，%s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
		return 0;
	}
	dbconnected = 1;
	return 1;
} /* 数据库开始 */

void database_end() {
	if (dbconected) mysql_close(&my_connection);
	dbconnected = 0;
} /* database_end */

int add_cd(char *srtist,-char *title, char *catalogue, int *cd_id) {
	MYSQL_RES *res_ptr;
	MYSQL_ROM mysqlrow;
	
	int res;
	char is[250];
	char es[250];
	int artist_id = -1;
	int new_cd_id = -1;
	
	if (!dbconnected) return 0;
	artist_id = get_artist_id(artist);
	mysql_escape_string(es, title, strlen(title));
	sprintf(is, "insert into cd(title, artist_id, catalogue)values('%s, %d, %d')", es, artist_id, catalogue);
	res = mysql_query(&my_connection, is);
	if (res) {
		fprintf(stderr, "输入错误%d：%s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
		return 0;
	}
}





