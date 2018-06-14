#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define MAXLINE 100

int main(int argc, char* argv[]) {
    int n, pid, fd[2];
    char line[MAXLINE];

    signal(SIGCHLD, SIG_IGN);
    pipe(fd);

    if((pid = fork()) == 0) {
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	execvp(argv[1], &argv[1]);
    }
    else {
	close(fd[1]);
	printf("자식 프로세스로부터 받은 결과\n");
	while((n = read(fd[0], line, MAXLINE)) > 0)
	    write(1, line, n);
    }

    exit(0);
}
