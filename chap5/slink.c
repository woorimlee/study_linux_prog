#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	if(argc < 3) {
		fprintf(stderr, "Using : ./%s old_file new_file", argv[0]);
		exit(1);
	}

	if(symlink(argv[1], argv[2]) == -1) {
		perror(argv[1]);
		exit(2);
	}

	exit(0);
}
