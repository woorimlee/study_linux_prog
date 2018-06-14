#include <stdio.h>
#include "student.h"

int main (int argc, char * argv[]) {
	student rec;
	FILE *fp;
	
	if(argc != 2) {
		fprintf(stderr, "Use : %s file\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "r");
	printf("%s %-4s %-4s\n", "num", "name", "score");
	
	while(fscanf(fp, "%d %s %d", &rec.id, rec.name, &rec.score) == 3) 
		printf("%d %s %d\n", rec.id, rec.name, rec.score);
	
	fclose(fp);
	return 0;
}

