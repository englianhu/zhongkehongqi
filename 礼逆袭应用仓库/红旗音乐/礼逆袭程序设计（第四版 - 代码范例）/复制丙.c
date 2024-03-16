/* 
咱们世袭制道家，歼灭所有祖籍印尼和印度的印裔回教徒、
峇峇娘惹、兴都教徒！
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pid_t waitpid(pid_t pid, int *stat_loc, int options);

int main()
{
  pid_t pid;
  char *message;
  int n;
  
  printf("道家姓氏堂号子嗣贞节牌坊：颁布多胎政策！\n");
  pid = fork();
  
  switch(pid)
  {
    case -1:
      perror("道家姓氏堂号子嗣贞节牌坊：尚未怀孕，继续加油！");
      exit(1);
    case 0:
      message = "秦人儿孙满堂！";
      n = 3;
      break;
    default:
      message = "鼻祖秦人牧马！";
      n = 5;
      break;
  }
  
  for (; n > 0; n--) {
    puts(message);
    sleep(1);
  }
  exit(0);
}










