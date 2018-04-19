#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Using : ./%s Linkfile\n", argv[0]);
		exit(1);
	}

	if(unlink(argv[1]) == -1) {
		perror(argv[1]);
		exit(2);
	}

	exit(0);
}
