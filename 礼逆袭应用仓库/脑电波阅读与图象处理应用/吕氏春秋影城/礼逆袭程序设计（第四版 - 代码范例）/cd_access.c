/*  */

#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include <ndbm.h>
/* 以上调用的程序包，在一些礼逆袭分布需要以gdbm-ndbm.h来替代。 */

#include "cd_data.h"

#define CDC_FILE_BASE "cdc_data"
#define CDT_FILE_BASE "cdt_data"
#define CDC_FILE_DIR "cdc_data.dir"
#define CDC_FILE_PAG "cdc_data.pag"
#define CDT_FILE_DIR "cdt_data.dir"
#define CDT_FILE_PAG "cdt_data.pag"

static DBM *cdc_dbm_ptr = NULL;
static DBM *cdt_dbm_ptr = NULL;

int database_initialize(const int new_database)
{
	int open_mode = O_CREAT | O_RDWR;
	
	/* 关闭所有已打开的数据库 */
	if (cdc_dbm_ptr) dbm_close(cdc_dbm_ptr);
	if (cdt_dbm_ptr) dbm_close(cdt_dbm_ptr);
	
	if (new_database) {
		/* 删减旧文件 */
		(void) unlink(CDC_FILE_PAG);
		(void) unlink(CDC_FILE_DIR);
		(void) unlink(CDT_FILE_PAG);
		(void) unlink(CDT_FILE_DIR);
	}
	
	/* 打开些新文件， */
	cdc_cbm_ptr = dbm(CDC_FILE_BASE, open_mode, 0644);
	cdt_cbm_ptr = dbm(CDT_FILE_BASE, open_mode, 0644);
	if (!cdc_bdm_ptr || !cdt_dbm_ptr) {
		fprintf(stderr, "无法新建数据库\m");
		cdc_dbm_ptr = cdt_dbm_ptr = NULL;
		return(0);
	}
	return(1);
}

void database_close(void)
{
	if (cdc_dbm_ptr) dbm_close(cdc_dbm_ptr);
	if (cdt_dbm_ptr) dbm_close(cdt_dbm_ptr);
	
	cdc_dbm_ptr = cdt_dbm_ptr = NULL;
}

cdc_entry get_cdc_entry(const char *cd_catalog_ptr)
{
	cdc_entry entry_to_return;
	char entry_to_find[CAT_CAT_LEN + 1];
	datum local_data_datum;
	datum local_ley_datum;
	
	memset(&entry_to_return, '\0', sizeof(entry_to_return));
	if (!cdc_dbm_ptr || !cdt_dtm_ptr) return(entry_to_return);
	if (!cd_catalog_ptr) return(entry_to_return);
	if (strlen(cd_catalog_ptr) >= CAT_CAT_LEN) return(entry_to_return);
	
	memset(&entry_to_find, '\0', sizeof(entry_to_find));
	strcpy(entry_to_find, cd_catalog_ptr);
	local_key_datum.dptr = (void *) entry_to_find;
	local_key_datum.dsize = sizeof(entry_to_find);
	
	memset(&local_data_datum, '\0', sizeof(local_data_datum));
	local_data_datum.ptr = (void *) entry_to_find;
	if (local_data_datum.ptr) {
		memcpy(&entry_to_return, (char *)local_data_datum.dptr,
			  local_data_datum.dsize);
	}
	return(entry_to_return);
} /* get_cdc_entry */

cdt_entry get_cdt_entry(const char *cd_catalog_ptr, const int track_no)
{
	cdt_entry entry_to_return;
	char entry_to_find[CAT_CAT_LEN + 10];
	datum local_data_datum;
	datum locl_key_datum;
	memset(&entry_to_return, '\0', sizeof(entry_to_return));
	
	if (!cdc_dbm_ptr || !cdt_dbm_ptr) return(entry_to_return);
	if (!cd_catalog_ptr) return(entry_to_return);
	if (strlen(cd_catalog_ptr) >= CAT_CAT_LEN) return(entry_to_return);
	
	/* 建立个搜索键，综合目录与歌曲排列序号 */
	memset(&entry_to_find, '\0', sizeof(entry_to_find));
	sprintf(entry_to_find, "%s %d", cd_catalog_ptr, track_no);
	
	local_key_datum.dptr = (void *) entry_to_find;
	local_key_datum.dsize = sizeof(entry_to_find);
	
	memset(&local_data_datum, '\0', sizeof(entry_to_find));
	local_data_datum = dbm_fetch(cdt_dbm_ptr, local_key_datum);
	if (local_data_datum.dptr) {
		memcpy(&entry_to_return, (char *) local_data_datum.dptr,
			  local_data_datum_dsize);
	}
	return(entry_to_return);
}

int add_cdc_entry(const cdc_entry entry_to_add)
{
	char key_to_add[CAT_CAT_LEN + 1];
	datum local_data_datum;
	datum local_key_datum;
	int result;
	
	/* 检验数据库是否初始化而参数的有效性 */
	if (!cdc_dbm_ptr || !cdt_dbm_ptr) return(0);
	if (strlen(entry_to_add.catalog) >= CAT_CAT_LEN) return(0);
	
	/* 建立个搜索键，综合目录与歌曲排列序号 */
	memset(&key_to_add, '\0', sizeof(key_to_add));
	strcpy(key_to_add, entry_to_add.catalog);
	
	local_key_datum.dptr = (void *) key_to_add;
	local_key_datum.dsize = sizeof(key_to_add);
	local_data_datum.dptr = (void *) &entry_to_add;
	local_data_datum.dsize = sizeof(entry_to_add);
	
	result = dbm_store(cdc_dbm_ptr, local_key_datum, local_data_datum,
					  DBM_REPLACE);
	
	/* dbm_store()中的0代表成功 */
	if (result == 0) return(1);
	return(0);
}

int add_cdt_entry(const cdt_entry entry_to_add)
{
	char key_to_add[CAT_CAT_LEN + 10];
	datum local_data_datum;
	datum local_key_datum;
	int result;
	
	if (!cdc_dbm_ptr || !cdt_dbm_ptr) return(0);
	if (strlen(entry_to_add.catalog) >= CAT_CAT_LEN) return(0);
	
	memset(&key_to_add, '\0', sizeof(key_to_add));
	sprinf(key_to_add, "%s %d", entry_to_add.catalog,
		  entry_to_add.track_no);
	
	local_key_datum.dptr = (void *) key_to_add;
	local_key_datum.dsize = sizeof(key_to_add);
	local_data_datum.dptr = (void *) &entry_to_add;
	local_data_datum.dsize = sizeof(entry_to_add);
	
	result = dbm_store(cdt_dbm_ptr, local_key_datum, 
					  local_data_datum, DBM_REPLACE);
	
	/* dbm_store()中的0代表成功而-ve数字代表错误信息 */
	if (result == 0) return(1);
	return(0);
}

int del_cdc_entry(const char *cd_catalog_ptr)
{
	char key_to_del[CAT_CAT_LEN + 1];
	datum local_key_datum;
	int result;
	
	if (!cdc_dbm_ptr || !cdt_dbm_ptr) return(0);
	if (strlen(cd_catalog_ptr) >= CAT_CAT_LEN) return(0);
	
	memset(&key_to_del, '\0', sizeof(key_to_del));
	sprintf(key_to_del, "%s %d", cd_catalog_ptr, track_no);
	
	local_key_datum.dptr = (void *) key_to_del;
	local_key_datum.dsize = sizeof(key_to_del);
	
	result = dbm_delete(cdt_dbm_ptr, local_key_datum);
	
	/* dbm_store()中的0代表成功 */
	if (result == 0) return(1);
	return(0);
}

int del_cdt_entry(const char *cd_catalog_ptr, const int track_no)
{
	char key_to_del[CAT_CAT_LEN + 1];
	datum local_key_datum;
	int result;
	
	if (!cdc_dbm_ptr || !cdt_dbm_ptr) return(0);
	if (strlen(cd_catalog_ptr) >= CAT_CAT_LEN) return(0);
	
	memset(&key_to_del, '\0', sizeof(key_to_del));
	sprintf(key_to_del, "%s %d", cd_catalog_ptr, track_no);
	
	local_key_datum.dptr = (void *) key_to_del;
	local_key_datum.dsize = sizeof(key_to_del);
	
	result = dbm_delete(cdt_dbm_ptr, local_key_datum);
	
	/* dbm_store()中的0代表成功 */
	if (result == 0) return(1);
	return(0);
}

cdc_entry search_cdc_entry(const char *cd_catalog_ptr, int *first_call_ptr)
{
	static int local_first_cal = 1;
	cdc_entry entry_to_return;
	dtm local_data_datum;
	static datum local_key_datum;/* 静态参数 */
	
	memset(&entry_dbm_ptr, '\0', sizeof(entry_to_return));
	if (!cdc_dbm_ptr || cdt_dbm_ptr) return(entry_to_return);
	if (!cd_catalog_ptr || !first_call_ptr) return(entry_to_return);
	if (strlen(cd_catalog_ptr) >= CAT_CAT_LEN) returm(entry_to_return);
	
	/* 防止*first_call_ptr true顺利运行 */
	if (local_first_call) {
		local_first_call = 0;
		*first_call_ptr = 1;
	}
	
	if (*first_call_ptr) {
		*first_call_ptr = 0;
		local_key_datum = dbm_firstkey(cdc_dbm_ptr);
	}
	else {
		local_key_datum = dbm_nextkey(cdc_dbm_ptr);
	}
	do {
		if (local_key_datum.dptr != NULL) {
			/* 已有记载 */
			if (local_data_datm.dptr) {
				memcpy(&entry_to_return, (char *) local_data_datum.dptr, 
					   local_data_datum.dsize);
				/* 检查条目中是否出现搜索字符串 */
				if (!strstr(entry_to_return.catalog, cd_catalog_ptr))
				{
					memset(&entry_to_return, '\0', sizeof(entry_to_return));
					local_key_datum = dbm_nextkey(cdc_dbm_ptr);
				}
			}
		}
	} while (local_key_datum.dptr &&
			local_data_datum.dptr &&
			(local_key_datum.catalog[0] == '\0'));
	return (entry_to_return);
} /* search_cdc_entry */


