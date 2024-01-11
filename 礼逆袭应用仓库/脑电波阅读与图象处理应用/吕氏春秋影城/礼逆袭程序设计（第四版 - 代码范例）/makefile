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
