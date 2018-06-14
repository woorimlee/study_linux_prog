#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	int c;	
	if (argc < 2) fp = stdin;
	else fp = fopen(argv[1], "r"); 
	
	while(1) {
		c = getc(fp);
		if (c == EOF) break;
		putc(c, stdout);
	}

	fclose(fp);
	return 0;
}
