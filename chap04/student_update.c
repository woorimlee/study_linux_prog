#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio_ext.h>
#include "student.h"

int main (int argc, char *argv[]) {
	int fd, id, a;
	char c = 'Y';
	student rec;

	if (argc < 2) {
		fprintf(stderr, "Use : %s studb1\n", argv[0]);
		exit(1);
	}

	if ((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	while(c == 'Y') {
		printf("Input student num to change it's info :");
		if (scanf("%d", &id) == 1) {
			__fpurge(stdin);
			lseek(fd,(id-START_ID)*sizeof(rec), SEEK_SET);
			if((read(fd, &rec, sizeof(rec)) >0) && (rec.id !=0)) {
				printf("student num :%2d\t name:%10s\t score:%4d\n", rec.id, rec.name, rec.score);
				printf("Now input new name :");
				scanf("%s%*c",rec.name);
				printf("And then input new score :");
				scanf("%d%*c", &rec.score);
				lseek(fd,-sizeof(rec), SEEK_CUR);
				printf("%s, %d\n", rec.name, rec.score);
				a = write(fd, &rec, sizeof(rec));
				printf("%d\n",a);
			}
			else printf("There's no record %d", id);
		}
		else printf("Input error\n");
		
		printf("Do you want to continue? (Y/N) :");
		scanf("%c", &c);
		__fpurge(stdin);
	}
	close(fd);
	exit(0);
}
