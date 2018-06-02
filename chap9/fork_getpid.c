#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();
    if(pid == 0) {
	printf("[%d] process's pid value : %d\n", getpid(), pid);
	exit(0);
    }
    wait(NULL);
    printf("[%d] process's pid value : %d\n", getpid(), pid);
    
    return 0;
}
