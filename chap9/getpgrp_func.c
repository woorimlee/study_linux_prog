#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    pid_t pid;

    printf("[Parent] PID = %d, GID = %d\n", getpid(), getpgrp());
    
    pid = fork();
    if(pid == 0) {
	printf("[CHILD] PID = %d, GID = %d\n", getpid(), getpgrp());
	exit(0);
    }

    waitpid(pid, 0, 0);
    return 0;
}

