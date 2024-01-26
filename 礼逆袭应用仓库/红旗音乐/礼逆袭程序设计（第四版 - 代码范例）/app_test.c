/*

引用：礼逆袭程序设计（第四版）第七百一十二页：第八章第第二节测试应用程序接口
https://github.com/englianhu/library/blob/%E4%B8%96%E5%8D%9A%E9%87%8F%E5%8C%96%E7%A0%94%E7%A9%B6%E9%99%A2/%E5%A7%8B%E7%A5%96%E6%B0%B8%E6%98%A5%E2%88%99%E7%A7%A6%E8%B0%8F%EF%BC%88%E8%AF%B8%E5%AD%90%E7%99%BE%E5%AE%B6%EF%BC%8C%E4%B8%AD%E6%96%87%E7%BC%96%E7%A8%8B%EF%BC%89/%E9%85%89%E9%80%86%E8%A2%AD%E4%B8%8E%E7%A4%BC%E9%80%86%E8%A2%AD/%E7%A4%BC%E9%80%86%E8%A2%AD%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%EF%BC%88%E7%AC%AC%E5%9B%9B%E7%89%88%EF%BC%89.pdf

- [「章」「节」「卷」「篇」「辑」「集」「部」等划分有规范性的用法么](https://www.zhihu.com/question/20362742)
- [「一卷书」的「卷」是怎样一个单位？](https://www.zhihu.com/question/20821237)
- [中国古人书写载体：椠、版、方、牍、简、牒、策、觚、帛、纸](https://baijiahao.baidu.com/s?id=1781595015562599076)
- [小说中的篇，章，部，回这几个量词有什么区别](https://zhidao.baidu.com/question/316864039.html)
- [如何用英文表示文章分段用的“篇、章、节”？](https://zhidao.baidu.com/question/533723183.html)
- [大仙儿语文知识积累，带你掌握高考语文必备知识点](https://www.zhihu.com/pin/1363223662141865984)
- [长篇章回小说,是章与回有什么联系?](https://qb.zuoyebang.com/xfe-question/question/662c6e85e6f061d4ac6d23e23988219a.html)
- [诗歌的“章、首、节”](https://www.zgshige.com/c/2018-05-18/6215619.shtml)

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "app_mysql.h"

int main() {
	struct 当前专辑 专辑;
	struct 搜索专辑 专辑收录;
	struct 当前歌曲 歌曲号;
	int 专辑序号;
	int res, i;
	
	databse_start("雷欧", "密码");
	
	成绩 = 添加专辑("中华古典民曲", "中华古典芳名榜", "二零零二", &专辑序号);
	printf("添加%d新专辑到收录，专辑序号是%d。\n", 专辑收录, 专辑序号);
	
	memset(&歌曲号, 0, sizeof(歌曲号));
	歌曲号.专辑序号 = 专辑序号;
	strcpy(歌曲号.歌曲[0], "莫问归期");
	strcpy(歌曲号.歌曲[1], "燕无歇");
	strcpy(歌曲号.歌曲[2], "等什么君");
	strcpy(歌曲号.歌曲[3], "落了白");
	strcpy(歌曲号.歌曲[4], "谁在以我留下的雷");
	strcpy(歌曲号.歌曲[5], "爱河");
	strcpy(歌曲号.歌曲[6], "再见中港路");
	strcpy(歌曲号.歌曲[7], "笑傲江湖");
	strcpy(歌曲号.歌曲[8], "我的唇吻不到我爱的人");
	strcpy(歌曲号.歌曲[9], "风夜行");
	strcpy(歌曲号.歌曲[10], "中国人");
	strcpy(歌曲号.歌曲[11], "黄种人");
	strcpy(歌曲号.歌曲[12], "我是中国人");
	strcpy(歌曲号.歌曲[12], "中国话");
	strcpy(歌曲号.歌曲[11], "龙的传人");
	strcpy(歌曲号.歌曲[11], "忘情水");
	strcpy(歌曲号.歌曲[12], "白鸽");
	strcpy(歌曲号.歌曲[13], "白狐");
	strcpy(歌曲号.歌曲[14], "相思的债");
	strcpy(歌曲号.歌曲[15], "我这一生");
	strcpy(歌曲号.歌曲[16], "红尘情歌");
	strcpy(歌曲号.歌曲[17], "不爱我就别伤害我");
	strcpy(歌曲号.歌曲[18], "再度重相逢");
	添加歌曲(&歌曲号);
	
	res = 检索("中国人", &专辑结果);
	printf("寻获%d专辑，首张专辑%d\n", res, 专辑收录.专辑序号[0]);
	
	res = 读取专辑(专辑收录.专辑序号[0], &专辑);
	printf("寻获专辑返回%d\n", 歌曲号);

	memset(&歌曲号, 0, sizeof(歌曲号));
	res = 寻获专辑歌曲(专辑成绩.专辑序号[0], &专辑);
	printf("寻获专辑歌曲返回%d\n", &歌曲号);
	printf("标题：%s\n", 专辑.标题);
	i = 0;
	while (i < res) {
		printf("\t歌曲%d是%s\n", i, 歌曲号.歌曲[i]);
		i++;
	}

	res = 删除专辑(专辑成绩.专辑序号[0]);
	printf("删除专辑返回%d\n", 专辑);

	databse_end();

	return EXIT_SUCCESS
}

int 寻获专辑(int , ) {
	
}



