#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio_ext.h>
#include "student.h"

int main(int argc, char *argv[]) {
	int fd, id;
	student rec;
	struct flock lock;
	
	if(argc < 2) { 
		fprintf(stderr, "Use : %s studb1 \n", argv[0]);
		exit(1);
	}	

	if((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		exit(2);
	}	

	printf("Input student's num to modify :");
	while(scanf("%d", &id) == 1) {
		__fpurge(stdin);	
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;	
		lock.l_start = (id-START_ID)*sizeof(rec);
		lock.l_len = sizeof(rec);	
		if(fcntl(fd, F_SETLKW, &lock) == -1) {
			perror(argv[1]);
			exit(3);
		}
	
		lseek(fd, (long)(id-START_ID)*sizeof(rec), SEEK_SET);
		if((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0)) {
			printf("name : %s\tnum : %d\tscore : %d\n", rec.name, rec.id, rec.score); }
		else printf("There's no record '%d' found\n", id);
		
		printf("Input score modified : ");
		scanf("%d", &rec.score);
		lseek(fd, (long)-sizeof(rec), SEEK_CUR);
		write(fd, &rec, sizeof(rec));

		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);
		printf("\n Input student's num to modify : ");
	}
	close(fd);
	exit(0);
}	
