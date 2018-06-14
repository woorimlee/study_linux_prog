#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio_ext.h>
#include "student.h"

int main(int argc, char * argv[]) {
	int fd, id;
	student rec;
	struct flock lock;
	
	if(argc < 2) {
		fprintf(stderr, "Use : %s studb1\n", argv[0]);
		exit(1);
	}

	if ((fd = open(argv[1], O_RDONLY))== -1) {
		perror(argv[1]);
		exit(2);
	}

	printf("\n Input student's num to read its info :");
	while(scanf("%d", &id) == 1) {
		__fpurge(stdin);
		lock.l_type = F_RDLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = (id-START_ID)*sizeof(rec);
		lock.l_len = sizeof(rec);
		if(fcntl(fd, F_SETLKW, &lock) == -1) {
			perror(argv[1]);
			exit(3);
		}
		
		lseek(fd, (id-START_ID)*sizeof(rec), SEEK_SET);
		if((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0)) printf("name : %s \tnum : %d \tscore : %d\n", rec.name, rec.id, rec.score);
		else printf("There's no record %d\n", id);

		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);
		printf("\n  Input student's num to read its info :");
	}

	close(fd);
	exit(0);
}
