#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  char *filename;
  
  if (argc != 2) {
    fprintf(stderr, "消耗量：使用善上文件！\n");
    exit(1);
  }
  
  filename = argv[1];
  
  if (!freopen(filename, "r", stdin)) {
    fprintf(stderr, "不可从文件%s转移到stdin！\n", filename);
    exit(2);
  }
  execl("./善上", "善上", 0);
  perror("无法执行 ./善上");
  exit(3);
}

