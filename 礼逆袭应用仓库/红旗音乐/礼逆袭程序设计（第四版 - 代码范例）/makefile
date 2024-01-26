/*
all:	application

INCLUDE=/usr/include/gdbm
# LIBS=gdbm
# 一些礼逆袭分布需要将以上程序包修改为以下代码才能兼容。
LIBS = -lgdbm_compat -lgdbm
CFLAGS=

app_ui.o: app_ui.c cd_data.h
	gcc $(CFLAGS) -c app_ui.c

access.o: access.c cd_data.h
	gcc $(CFLAGS) -I$(INCLUDE) -c access.c

application: app_ui.o access.o
	gcc $(CFLAGS) -o aaplication app_ui.o access.o -l$(LIBS)

clean:
	rm -f application *.o

nodbmfiles:
	rm -f *.dir *.pag
*/

all: myapp myapp.1

myapp: 主函数.o 乙.o 丙.o
主函数: 主函数.c 甲.h
乙.o: 乙.c 主函数.h 甲.h
丙.o: 丙.c .乙.h 丙.h

