#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ndbm.h>
/*	一些非主流操作系统需要调用 #include <gdbm-ndbm.h> */
#include <string.h>

#define TEST_DB_FILE "/tmp/dbm2_test"
#define ITEMS_USED 3

struct test_data {
	char misc_chars[15];
	int any_integer;
	char more_chars[21];
};

int main()
{
	struct test_data items_to_store[ITEMS_USED];
	struct test_data item_retrieved;

	char key_to_use[20];
	int i, result;

	datum key_datum;
	datum data_datum;

	DBM *dbm_ptr;
	dbm_ptr = dbm_open(TEST_DB_FILE, O_RDWR | O_CREAT, 0666);
	if (!dbm_ptr) {
		fprintf(stderr, "打开数据库失败\n");
		exit(EXIT_FAILURE);
	}

	memset(items_to_store, '\0', sizeof(items_to_store));
	strcpy(items_to_store[0].misc_chars, "首次！");
	items_to_store[0].any_integer = 47;
	strcpy(items_to_store[0].more_chars, "符");
	
	strcpy(items_to_store[1].more_chars, "闩");
	items_to_store[1].any_integer = 13;
	strcpy(items_to_store[1].more_chars, "不巧？");

	strcpy(items_to_store[2].more_chars, "三");
	items_to_store[2].any_integer = 3;
	strcpy(items_to_store[2].more_chars, "高雅");

	for (i = 0; i < ITEMS_USED; i++) {
		sprintf(key_to_use, "%c%c%d",
				items_to_store[i].misc_chars[0],
				items_to_store[i].more_chars[0],
				items_to_store[i].any_integer);
		
		key_datum.dptr = (void *)key_to_use;
		key_datum.dsize = strlen(key_to_use);
		data_datum.dptr = (void *)&items_to_store[i];
		data_datum.dsize = sizeof(struct test_data);
		
		result = dbm_store(dbm_ptr, key_datum, data_datum, DBM_REPLACE);
		if (result != 0) {
			fprintf(stderr, "dbm_store在公钥%s\n失败", key_to_use);
			exit(2);				
		}
	}
	/* 现在尝试削减数据 */
	sprintf(key_to_use, "非%d", 13);
	key_datum.dptr = key_to_use;
	key_datum.dsize = strlen(key_to_use);
	
	if (dbm_delete(dbm_ptr, key_datum) == 0) {
		printf("删除公钥%s的数据\n", key_to_use);
	}
	else {
		printf("公钥%s的数据并无删除\n", key_to_use);
	}
	
	for (key_datum = dbm_firstkey(dbm_ptr);	key_datum.dptr;
		 key_datum = dbm_nextkey(dbm_ptr)) {
		data_datum = dbm_fetch(dbm_ptr, key_datum);
		if (data_datum.dptr) {
			printf("已接收的数据\n");
			memcpy(&item_retrieved, data_datum.dptr, data_datum.dsize);
			printf("纠正/挽回数据 - %s %d %s\n",
				item_retrieved.misc_chars,
				item_retrieved.any_integer,
				item_retrieved.more_chars);
		}
		else {
			printf("在公钥%s中查无数据\n", key_to_use);
		}
	}
	dbm_close(dbm_ptr);
	exit(EXIT_SUCCESS);
}



