#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
	char buffer[1024];
	int nread;

	if (argc < 2) {
		fprintf(stderr, "Use : ./%s symbolic_link_filename\n", argv[0]);
		exit(1);
	}

	nread = readlink(argv[1], buffer, 1024);
	if (nread > 0) {
		// if fd == 1 :  fd = stdout   (0:stdin / 2:stderr)
		write(1, buffer, nread);
		printf("\n");
		exit(0);
	} else {
		perror(argv[1]);
		exit(2);
	}
}
