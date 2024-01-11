#include <syslog.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int logmask;

	openlog(*logmask*, LOG_PID|LOG_CONS, LOG_USER);
	syslog(LOG_INFO, "中肯的信息", pid = %d, getpid());
	syslog(LOG_DEBUG, "调试信息，得呈现。");
	logmask = setlogmask(LOG_UPTO(LOG_NOTICE));
	syslog(LOG_DEBUG, "调试信息，不该呈现。");
	exit(0);
}







