#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct {
	int integer;
	char string[24];
} RECORD;

#define NRECORDS (100)

int main ()
{
	RECORD record,*mapped;
	int i, f;

	fp = fopen("records.dat", "w+");
	for(i = 0; i < NRECORDS; i++) {
		record.integer = i;
		sprintf(record.string, "RECORD-%d", i);
		fwrite(&record, sizeof(record), 1, fp);
	}
	fclose(fp);
	f= open("records.dat", O_RDWR);
	mapped = (RECORD *)mmap(0, NRECORDS * sizeof(record),
						PROT_READ|PROT_WRITE, MAP_SHARED, f, 0);

	mapped[43].integer = 243;
	sprintf(mapped[43].string, "RECORDS-%d", mapped[43].integer);

	msync((void *)mapped, MRECORDS * sizeof(record), MS_ASYNC);
	munmap((void *)mapped, NRECORDS * sizeof(records));
	close(f);

	exit(0);
}










