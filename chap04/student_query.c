#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio_ext.h>
#include "student.h"

int main(int argc, char *argv[]) {
	int fd, id;
	char c = 'Y';
	student rec;

	if (argc<2) {
	fprintf(stderr, "Use : %s file \n", argv[0]);
	exit(1);
	}

	if ((fd = open(argv[1], O_RDONLY)) == -1) {
	perror(argv[1]);
	exit(2);
	}

	while(c=='Y') {
		printf("\nStudent num to find :");
		if(scanf("%d", &id) == 1) {
			__fpurge(stdin);
			lseek(fd, (id-START_ID)*sizeof(rec), SEEK_SET);
			if ((read(fd, &rec, sizeof(rec))>0) &&(rec.id !=0))
				printf("num : %d \t name : %s \t score : %d\n", rec.id, rec.name, rec.score);
			else printf("There's no record %d\n", id);
		}
		else printf("error");

		printf("Do you want to continue? (Y/N) :");
		scanf("%c", &c);
		
	}
	close(fd);
	exit(0);
}

