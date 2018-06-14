#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <utime.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	struct stat buf;
	struct utimbuf time; //time_t actime, time_t modtime
	if (argc < 3) {
		fprintf(stderr, "Using : cptime file1 file2\n");
		exit(1);
	}

	if (stat(argv[1], &buf) < 0) {
		perror("stat()");
		exit(2);
	}

	time.actime = buf.st_atime;
	time.modtime = buf.st_mtime;

	int return_vlu = utime(argv[2], &time);
	printf("return value : %d\n",return_vlu);
	if(return_vlu){
		printf("fail\n");
		perror("utime");
	}
	else {
		printf("success\n");
		exit(0);
	}
}

