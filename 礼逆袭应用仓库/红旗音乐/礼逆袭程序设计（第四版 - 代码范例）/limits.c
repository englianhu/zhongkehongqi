#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void work()
{
	FILE *f;
	int i;
	double x = 4.5;

	f = tmpfile();
	for(i = 0; i < 10000; i++) {
		fprintf(f, "得作出成效\n");
		if(ferror(f)) {
			fprintf(stderr, "错误信息皆记载至临时文件\n");
			exit(1);
		}
	}
	for(i = 0; i < 1000000; i++)
		x = log(x * x + 3.21);
}

int main()
{
	struct rusage r_usage;
	struct rlimit r_limit;
	int priority;

	work();
	getrusage(RUSAGE_SELF, &r_usage);

	printf("中央处理单位消耗量：用户=%ld.%06ld, 系统=%ld.%061d\n", 
		r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec,
		r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);

		priority = getpriority(PRIO_PROCESS, getpid());
		printf("目前优先事项=%d\n", priority);

		getrlimit(RLIMIT_FSIZE, &r_limit);
		printf("目前文件体积规模上制：软件 = %ld，硬件 = %ld\n",
			r_limit.rlim_cur, r_limit.rlim_max);
		
		r_limit.rlim_cur = 2048;
		r_limit.rlim_max = 4096;
		printf("设置个体积规模上限为两千字节的文件\n");
		setrlimit(RLIMIT_FSIZE, &r_limit);

		work();
		exit(0);
}









