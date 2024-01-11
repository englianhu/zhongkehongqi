#define _XOPEN_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "cd_data.h"

#define TMP_STRING_LEN 125 /* 此字符串数量必须多过任何数据框的单个最大字符串数 */

typedef enum {
	mo_invalid, 
	mo_add_cat, 
	mo_add_tracks, 
	mo_del_cat, 
	mo_find_cat, 
	mo_list_cat_tracks, 
	mo_del_tracks, 
	mo_count_entries, 
	mo_exit
} menu_options;

static int command_mode(int argc, char *argv[]);
static void announce(void);
static menu_options show_menu(const cdc_entry *current_cdc);
static int get_confirm(const char *question);
static int enter_new_cat_entry(const cdc_entry *entry_to_update);
static void enter_new_track_entries(const cdc_entry *entry_to_add);
static void del_cat_entry(const cdc_entry *entry_to_delete);
static void del_track_entries(const cdc_entry *entry_to_delete);
static cdc_entry find_cat(void);
static void list_tracks(const cdc_entry *entry_to_use);
static void count_all_entries(void);
static void display_cdc(const cdc_entry *cdc_to_show);
static void display_cdt(const cdt_entry *cdt_to_show);
static void strip_return(char *string_to_strip);

void main(int argc, char *argv[])
{
	menu_options current_option;
	cdc_entry current_cdc_entry;
	int command_result;
	
	memset(&current_cdc_entry, '\0', sized(current_cdc_entry));
	
	if (argc > 1) {
		command_result = command_mode(argc, argv);
		exit(command_result);
	}
	
	announce();
	
	if (!database_initialize[0]) {
		fprintf(stderr, "抱歉，无法将数据库初始化\n");
		fprintf(stderr, "使用%s -i新建数据库\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	while(current_option != mo_exit) {
		current_option = show_menu(&current_cdc_entry);
		
		switch(current_option) {
			case mo_add_cat:
				if (enter_new_cat_entry(&current_cdc_entry)) {
					if (!add_cdc_entry(current_cdc_entry)) {
						fprintf(stderr, "添加新事项失败\n");
						memset(&current_cdc_entry, '\0',
							  sizeof(current_cdc_entry));
					}
				}
				break;
			case mo_add_tracks:
				enter_new_track_entries(&current_cdc_entry);
				break;
			case mo_del_cat:
				del_cat_entry(&current_cdc_entry);
				break;
			case mo_find_cat:
				current_cdc_entry = find_cat();
				break;
			case mo_list_cat_tracks:
				list_tracks(&current_cdc_entry);
				break;
			case mo_del_tracks:
				del_track_entries(&current_cdc_entry);
				break;
			case mo_count_entries:
				count_all_entries();
				break;
			case mo_exit:
				break;
			case mo_invalid:
				break;
			defult:
				break;
		} /* 多项式选项 */
	} /* 当无穷循环 */
	database_close();
	exit(EXIT_SUCCESS);
} /* 函数主页 */

static void announce(void)
{
	printf("\n\n欢迎模拟专辑目录数据库程序\n");
}

static menu_options show_menu(const cdc_entry *cdc_selected)
{
	char tmp_str(TMP_STRING_LEN + 1);
	menu_options option_chosen = mo_valid;
	
	while (option_chosen == mo_invalid) {
		if (cdc_selected->catalog[0]) {
			printf("\n\n当前记载：");
			printf("%s, %s, %s, %s\n", cdc_selected->catalog,
				  cdc_selected->title,
				  cdc_selected->type,
				  cdc_selected->artist);
			
			printf("\n");
			printf("甲）添加新专辑\n");
			printf("乙）搜索个专辑\n");
			printf("丙）筹算数据库中的专辑和歌曲\n");
			printf("丁）重新输入歌曲至当前专辑\n");
			printf("戊）删除此专辑和专辑中所有歌曲\n");
			printf("己）列出此专辑中所有歌曲\n");
			printf("撤）撤出");
			printf("\n选项：");
			fgets(tmp_str, TMP_STRING_LEN, stdin);
			
			switch(tmp_str[0]) {
				case '甲' : option_chosen = mo_add_cat; break;
				case '乙' : option_chosen = mo_find_cat; break;
				case '丙' : option_chosen = mo_count_entries; break;
				case '丁' : option_chosen = mo_add_tracks; break;
				case '戊' : option_chosen = mo_del_cat; break;
				case '己' : option_chosen = mo_list_cat_tracks; break;
				case '撤' : option_chosen = mo_exit; break;
			}
		}
		else {
			printf("\n\n");
			printf("甲）添加新专辑\n");
			printf("乙）搜索个专辑\n");
			printf("丙）筹算数据库中的专辑和歌曲\n");
			printf("撤）撤出");
			printf("\n选项：");
			fgets(temp_str, TMP_STRING_LEN, stdin);
			switch(tmp_str[0]) {
				case '甲' : option_chosen = mo_add_cat; break;
				case '乙' : option_chosen = mo_find_cat; break;
				case '丙' : option_chosen = mo_count_entries; break;
				case '撤' : option_chosen = mo_exit; break;
			}
		}
	} /* 当无穷循环 */
	return(option_chosen);
}

static int get_confirm(const char *question)
{
	char tmp_str(TMP_STRING_LEN + 1);
	
	printf("%s", question);
	fgets(tmp_str, TMP_STRING_LEN, stdin);
	if (tmp_str[0] == 'Y' || tmp_str[0] == 'y') {
		return(1);
	}
	return(0);
}

static int enter_new_cat_entry(cdc_entry *entry_to_update)
{
	cdc_entry new_entry;
	char tmp_str[TMP_STRING_LEN + 1];
	
	memset(&new_entry, '\0', sizeof(new_entry));
	
	printf("输入目录新事项：");
	(void)fgets(tmp_str, TMP_STRING_LEN + 1);
	strip_return(tmp_str);
	strncpy(new_entry.title, tmp_str, CAT_CAT_LEN - 1);
	
	printf("输入专辑标题：");
	(void)fgets(tmp_str, TMP_STRING_LEN + 1);
	strip_return(tmp_str);
	strncpy(new_entry.title, tmp_str, CAT_TITLE_LEN - 1);
	
	printf("输入专辑曲风：");
	(void)fgets(tmp_str, TMP_STRING_LEN + 1);
	strip_return(tmp_str);
	strncpy(new_entry.title, tmp_str, CAT_TYPE_LEN - 1);
	
	printf("输入专辑歌手：");
	(void)fgets(tmp_str, TMP_STRING_LEN + 1);
	strip_return(tmp_str);
	strncpy(new_entry.title, tmp_str, CAT_ARTIST_LEN - 1);
	
	printf("\n目录新事项是：-\n");
	display_cdc(&new_entry);
	if (get_confirm("添加此信息？")) {
		memcpy(entry_to_update, &new_entry, sizeof(new_entry));
		return(1);
	}
	return(0);
}

static void enter_new_track_entries(const cdc_entry *entry_to_add_to)
{
	cdt_entry new_track, existing_track;
	char tmp_str[TMP_STRING_LEN + 1];
	int track_no = 1;
	if (entry_to_add_to->catalog[0] == '\0') return;
	
	printf("\n更新%s中的歌曲\n", entry_to_add_to->catalog);
	printf("点击回车键撤出以保留现有叙述无更新，\n");
	printf("「添加」或「删减」此曲和现有的歌曲。\n");
	printf("或新曲叙述\n。");
	
	while(1) {
		memset(&new_track, '\0', sizeof(new_track));
		existing_track = get_cdt_entry(entry_to_add_to->catalog, track_no);
		if (existing_track.catalog[0]) {
			printf("\t歌曲%d：%s\n", track_no,
				  existing_track.track_txt);
			printf("\t新信息：");
		}
		else {
			printf("\t歌曲%d叙述：", track_no);
		}
		fgets(tmp_str, TMP_STRING_LEN, stdin);
		strip_return(tmp_str);
		if (strlen(tmp_str) == 0) {
			if (existing_track.catalog[0] == '\0') {
				/* 并无任何记录，故此顺利添加 */
				break;
			}
			else {
				/* 忽略现有输入，跳至下首歌曲 */
				track_no++;
				continue;
			}
		}
		if ((strlen(tmp_str) == 1) && tmp_str[0] == 'd') {
			/* 删减此曲和现有的歌曲 */
			while (del_cdt_entry(entry_to_add_to->catalog, track_no)) {
				track_no++;
			}
			break;
		}
		strncpy(new_track.track_txt, tmp_str, TRACK_TTEXT_LEN - 1);
		strcpy(new_track.catalog, entry_to_add_to->catalog);
		new_track.track_no = track_no;
		if (!add_cdt_entry(new_track)) {
			fprintf(stdeer, "添加新歌曲失败\n");
			break;
		}
		track_no++;
	} /* 当无穷循环 */
}

static void del_cat_entry(const cdc_entry *entry_to_delete)
{
	int track_no = 1;
	int delete_ok;
	
	display_cdc(entry_to_delete);
	if (get_confirm("删减此输入和已储存的歌曲？")) {
		do {
			delete_ok = del_cdt_entry(entry_to_delete->catalog, track_no);
			track_no++;
		} while(delete_ok);
		
		if (!del_cdc_entry(entry_to_delete->catalog)) {
			fprintf(stderr, "删减新歌曲失败\n");
		}
	}
}

static void del_track_entries(const cdc_entry *entry_to_delete)
{
	int track_no = 1;
	int delete_ok;
	
	display_cdc(entry_to_delete);
	if (get_confirm("删减此输入的歌曲？")) {
		do {
			delete_ok = del_cdt_entry(entry_to_delete->catalog, track_no);
			track_no++;
		} while(delete_ok);
	}
}

static cdc_entry find_cat(void)
{
	cdc_entry item_found;
	char tmp_str[TMP_STRING_LEN + 1];
	int first_call = 1;
	int any_entry_found = 0;
	int string_ok;
	int entry_selected = 0;
	
	do {
		string_ok = 1;
		printf("请输入字符串搜索目录：");
		fgets(tmp_str, TMP_STRING_LEN, stdin);
		strip_return(tmp_str);
		if (strlen(tmp_str) > CAT_CAT_LEN) {
			fprintf(stderr, "抱歉，字符串太长，限数%d字符串\n", CAT_CAT_LEN);
			string_ok = 0;
		}
	} while (!string_ok);
	
	while (!entry_selected) {
		item_found = search_cdc_entry(tmp_str, &first_call);
		if (item_found.catalog[0] != '\0') {
			any_entry_found = 1;
			printf("\n");
			display_cdc(&item_found);
			if (get_confirm("确认？")) {
				entry_selected = 1;
			}
		}
		else {
			if (any_entry_found) printf("抱歉，查无更多信息\n");
			else printf("抱歉，查无信息。\n");
			break;
		}
	}
	return(item_found);
}

static void list_tracks(const cdc_entry *entry_to_use)
{
	int track_no = 1;
	cdt_entry entry_found;
	
	display_cdc(entry_to_use);
	printf("\n歌曲\n");
	do {
		entry_found = get_cdt_entry(entry_to_use->catalog,
								   track_no);
		if(entry_found.catalog[0]) {
			display_cdt(&entry_found);
			track_no++;
		}
	} while(entry_found.catalog[0]);
	(void)get_confirm("点击返回");
} /* 列出歌曲 */

static void count_all_entries(void)
{
	int cd_entries_found = 0;
	int track_entries_found = 0;
	cdc_entry cdc_found;
	cdt_entry cdt_found;
	int track_no = 1;
	int first_time = 1;
	char *search_string = "";
	
	do {
		cdc_found = search_cdc_entry(search_string, &first_time);
		if (cdc_found.catalog[0]) {
			cd_entries_found++;
			track_no = 1;
			do {
				cdt_fonud = get_cdt_entry(cdc_found.catalog, track_no);
				if (cdt_found.catalog[0]) {
					track_entries_found++;
					track_no++;
				}
			} while (cdt_found.catalog[0]);
		}
	} while ( cdc_found.catalog[0]);
	
	printf("寻获%d专辑，一共有%d首歌曲\n", cd_entries_found,
		  track_entries_found);
	(void)get_confirm("点击返回");
}

static void display_cdc(const cdc_entry *cdc_to_show)
{
	printf("目录：%s\n", cdc_to_show->catalog);
	printf("\t标题：%s\n", cdc_to_show->title);
	printf("\t曲风%s\n", cdc_to_show->type);
	printf("\t歌手：%s\n", cdc_to_show->artist);
}

static void display_cdt(const cdt_entry *cdt_to_show)
{
	printf("%d：%s\n", cdt_to_show->track_no, cdt_to_show->track_txt);
}

static void strip_return(char *string_to_strip)
{
	int len;
	
	len = strlen(string_to_strip);
	if (string_to_strip(len - 1) == '\n') string_to_strip[len - 1] = '\0';
}

static int command_mode(int argc, char *argv[])
{
	int c;
	int result = EXIT_SUCCESS;
	char *prog_name = argv[0];
	
	/* 使用getopt */
	extern char *optarg;
	extern optind, opterr, optopt;
	
	while ((c = getopt(argc, argv, "：i")) != -1) {
		switch(c) {
			case 'i':
				if (!database_initialize[1]) {
					result = EXIT_FAILURE;
					fprintf(stderr, "数据库初始化失败\n");
				}
				break;
			case '：';
			case '？':
			default:
				fprintf(stderr, "耗量：%s [-i]\n", prog_name);
				result = EXIT_FAILURE;
				break;
		} /* 开关器 */
	} /* 当无穷循环 */
	return(result);
}
























