#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
char **environ;

int execl(const char *path, const char *arg0, ..., (char *)0);
int execlp(const char *file, const char *arg0, ..., (char *)0);
int execle(const char *path, const char *arg0, ..., (char *)0, char *const envp[]);
int execv(const char *path, char *const argv[]);
int exevp(const char *file, char *const argv[]);
int execve(const char *path, char *const argv[], char *const envp[]);
*/

/* 参数列表范例 */
/* 铭记咱们需要为argv[0]参数的程序命名 */
char *const ps_argv[] = {"ps", "ax", 0};

/* 环境设置范例并不好使 */
char *const ps_envp[] = {"PATH=/bin:/usr/bin", "TERM=console", 0};

int main()
{
	printf("通过系统运行PS！\n");
	
	/* 可以调试exec系列函数如下 */
	execl("/bin/ps", "ps", "ax", 0);           /* 假设ps程序储存于/bin文件夹 */
	execlp("ps", "ps", "ax", 0);               /* 假设/bin的路径名称是PATH */
	execle("/bin/ps", "ps", "ax", 0, ps_envp); /* 成功通过自家环境设置检验 */
	
	execv("/bin/ps", ps_argv);
	execvp("ps", ps_argv);
	execve("/bin/ps", ps_argv, ps_envp);
	
	printf("完成！\n");
	exit(0);
}







