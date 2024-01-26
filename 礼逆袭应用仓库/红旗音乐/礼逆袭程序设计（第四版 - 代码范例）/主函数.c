/* 主函数.c */

#include <stdlib.h>
#include "甲.h"

extern void 函数乙();
extern void 函数丙();

int main()
{
	函数乙();
	函数丙();
	exit(EXIT_SUCCESS);
}




