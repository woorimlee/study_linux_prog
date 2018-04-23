#include <stdio.h>
#define MAXLINE 80

int main(int argc, char *argv[]) {
	FILE *fp;
	int line = 0;
	char buffer[MAXLINE];
	char line_buffer[MAXLINE];
	
	if(argc != 2) {
		fprintf(stderr, "Use : ./line_count file \n");
		return 1;
	}
	
	if((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "File open failed\n");
		return 2;
	}

	while(fgets(buffer, MAXLINE, fp) != NULL) {
		line++;
		sprintf(line_buffer, "%3d %s", line, buffer);
		fputs(line_buffer, stdout);
		//printf("%3d %s", line, buffer);
	}

	return 0;
}
