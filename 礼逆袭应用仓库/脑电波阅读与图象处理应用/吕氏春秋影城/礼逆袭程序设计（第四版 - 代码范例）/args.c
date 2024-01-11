#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int arg;

	for(arg = 0; arg < argc; arg++) {
		if(argv[arg][0] == '-')
			printf("");
	}
	exit(0);
}









