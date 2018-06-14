#include <stdio.h>
//#include <stdio_ext.h>
#include "student.h"

int main(int argc, char *argv[]) {
	student rec;
	FILE *fp;
	
	if (argc != 2) {
		fprintf(stderr, "USE : %s file \n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "w");
	printf("%s %-6s %-4s\n", "num", "name", "score");
	
	while(scanf("%d %s %d", &rec.id, rec.name, &rec.score) == 3){ 
//		__fpurge(stdin);
		fprintf(fp, "%d %s %d ", rec.id, rec.name, rec.score);
	}
	
	fclose(fp);	
	return 0;
}
