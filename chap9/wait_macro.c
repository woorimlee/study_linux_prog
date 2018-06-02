#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (void) {
    int status;
    pid_t pid;

    if(!fork()) {
	sleep(1);
	//exit(0);
	abort();
    }

    pid = wait(&status);

    if(pid == -1) {
	perror("wait");
	printf("pid = %d\n", pid);
    }

    if(WIFEXITED(status)) printf("Normal termination with exit status = %d\n", WEXITSTATUS(status));
    if(WIFSIGNALED(status)) printf("Killed by signal = %d\n", WTERMSIG(status));
    if(WIFSTOPPED(status)) printf("Stopped by signal = %d\n", WSTOPSIG(status));
    if(WIFCONTINUED(status)) printf("Continued\n");

    return 0;
}

