#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char*argv[]) {
    int fd, status;
    pid_t pid;

    pid = fork();
    if(pid == 0) {
	fd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY,0600);
	dup2(fd,1);
	close(fd);
	execvp(argv[2], &argv[2]);
	fprintf(stderr, "%s : error\n", argv[1]);
    }
    else {
	wait(&status);
	printf("[%d]'s child process %d called exit()\n", getpid(), pid);
    }
}
