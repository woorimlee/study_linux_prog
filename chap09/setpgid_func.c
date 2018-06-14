#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
    pid_t pid;

    printf("[Parent] PID = %d, GID = %d\n", getpid(), getpgrp());

    pid = fork();
    if(pid == 0) {
	printf("[Child] PID = %d, GID = %d\n", getpid(), getpgrp());
	setpgid(0, 0);
	printf("[Child] PID = %d, GID = %d\n", getpid(), getpgrp());
	exit(0);
    }
    wait(NULL);

    exit(0);
}

