#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio_ext.h>
#include "student.h"

int main(int argc, char *argv[]) {
	int fd, id;	
	student rec;
	
	if(argc < 2) {
		fprintf(stderr, "Use : %s studb1\n", argv[0]);
		exit(1);	
	}

	if((fd = open(argv[1], O_RDWR)) == -1 ) {
		perror(argv[1]);
		exit(2);
	}

	printf("\n Input student's num to modify : ");
	while(scanf("%d", &id) == 1) {
		lseek(fd, (long)(id-START_ID)*sizeof(rec), SEEK_SET);
		if(lockf(fd, F_LOCK, sizeof(rec)) == -1) {
			perror(argv[1]);
			exit(3);
		}
		if((read(fd,&rec, sizeof(rec))>0) && (rec.id != 0))
			printf("name : %s\tnum : %d\t score : %d\n", rec.name, rec.id, rec.score);
		else printf("There's no record %d \n", id);

		printf("Input score to modify it's old score : ");
		scanf("%d", &rec.score);
		lseek(fd, (long)-sizeof(rec), SEEK_CUR);
		write(fd, &rec, sizeof(rec));
	
		lseek(fd, (long)(id-START_ID)*sizeof(rec), SEEK_SET);
		lockf(fd, F_ULOCK, sizeof(rec));
		printf("\n Input student's num to modify : ");
	}

	close(fd);
	exit(0);
}
