#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if(argc < 3) {
		fprintf(stderr, "Using : %s old_filename new_filename\n", argv[0]);
		exit(1);
	}

	if(link(argv[1], argv[2]) == -1) {
		exit(2);
	}

	exit(0);
}

