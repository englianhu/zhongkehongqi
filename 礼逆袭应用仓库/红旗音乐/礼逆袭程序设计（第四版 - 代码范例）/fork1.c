/* 复制 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  pid_t pid;
  char *message;
  int n;
  
  printf("复制程序行动启动！\n");
  pid = fork();
  
  switch(pid)
  {
    case -1:
      perror("复制失败！");
      exit(1);
    case 0:
      message = "儿孙于此！";
      n = 5;
      break;
    default:
      message = "鼻祖于此！";
      n = 3;
      break;
  }
  
  for (; n > 0; n--) {
    puts(message);
    sleep(1);
  }
  exit(0);
}










