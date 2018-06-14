#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main() {
	int fd1, fd2;

	if((fd1 = creat("./dup_test",0644)) == -1) 
		perror("dup_test");

	write(fd1, "Hello! Linux\n", strlen("Hello! Linux\n"));
	fd2 = dup(fd1);
	write(fd2, "Bye! Linux\n", 12);
	
	exit(0);
}
