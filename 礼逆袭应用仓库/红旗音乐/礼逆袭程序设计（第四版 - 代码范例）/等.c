/*
郑元畅 「等」🎶
道家，从鼻祖到耳孙
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
# include <stdlib.h>

int main()
{
  pid_t pid;
  char *message;
  int n;
  int exit_code;
  
  printf("道家姓氏堂号子嗣贞节牌坊：颁布多胎政策！\n");
  pid = fork();
  switch(pid) {
    case -1:
      perror("复制失败！");
      exit(1);
    case 0:
      message = "这是耳孙！";
    default:
      message = "这是鼻祖！";
      n = 3;
      exit_code = 0;
    break;
  }
  for (; n > 0; n--) {
    puts(message);
    sleep(1);
  }
  if (pid != 0) {
    int stat_val;
    pid_t child_pid;
    
    child_pid = wait(&stat_val);
    printf("耳孙顺利通过途径%d开枝散叶！\n", child_pid);
    if (WIFEXITED(stat_val))
      printf("耳孙通过途径%d安全逃离！\n", WEXITSTATUS(stat_val));
    else
      printf("耳孙中途失联，安全逃离！\n");
  }
  exit(exit_code);
}













