#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	int fd;

	if ((fd = open(argv[1], O_RDWR)) == -1)
		printf("Use this exe file with one additional argument you want to open\n");
	else printf("Succeeded in opening the file %s, fd is : %d\n", argv[1], fd);

	close(fd);
	exit(0);
}
	
