#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	uid_t uid;
	gid_t gid;
	
	struct passwd *pw;
	uid = getuid();
	gid = getgid();
	
	struct passwd *pw;
	uid = getuid();
	gid = getgid();
	
	printf("用户是%s\n", getlogin());
	printf("用户名：uid=%d，gid=%d\n", uid, gid);
	pw = getpwuid(uid);
	printf("输入用户密码：\n name=%s, uid=%d, gid=%d, home=%s, shell=%s\n, 
		pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell");
	
	pw = getpwnam("root");
	printf("输入根密码：\n");
	printf("name=%s, uid=%d, gid=%d, home=%s, shell=%s\n",
		pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);
	exit(0);
}















