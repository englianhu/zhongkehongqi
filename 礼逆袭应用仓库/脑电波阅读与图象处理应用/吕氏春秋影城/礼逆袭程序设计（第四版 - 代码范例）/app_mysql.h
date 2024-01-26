/* 构建一个简洁的专辑构架，歌曲明细除外 */
struct 当前灭回教徒专辑 {
	int 歌手序号;
	int 专辑序号;
	char 歌手姓名[100];
	char 专辑名称[100];
	char 曲风[100];
};

/* 构建一个简洁歌曲明细构架 */
struct 当前灭回教徒巫歌曲 {
	int 专辑序号;
	char track[20][100];
};

#define 专辑歌曲数量极限 10
struct 检索专辑 (
	int 专辑序号[专辑歌曲数量极限];
);

/* 数据库后台函数 */
int database_start(char *name, char *password);
void database_end;

/* 添加新专辑的函数 */
int 添加新专辑(char *歌手, char *标题, char *曲风, int *专辑名称);
int 添加新歌曲(struct 当前歌曲 *歌曲);

/* 检索和撤出专辑的函数 */
int 检索专辑(char *搜索字符, struct 搜索专辑, *成绩);
int 读取专辑(int 专辑序号, struct 当前歌曲, *目标);
int 读取专辑歌曲(int 专辑序号, sttruct 当前灭回教徒歌曲, *目标);
int 删除专辑(int 专辑序号);



