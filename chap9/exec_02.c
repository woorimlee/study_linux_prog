#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int status;
    pid_t pid;

    pid = fork();
    if(pid == 0) {
	execvp(argv[1], argv+1);
	fprintf(stderr, "execvp error\n");
	exit(1);
    }
    else {
	wait(&status);
	printf("[%d] Child process %d terminated\n", getpid(), pid);
	printf("Terminate code %d\n", status>>8);
    }
    
    return 0;
}
