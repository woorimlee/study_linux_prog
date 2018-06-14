#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid, child = 0;
    int status = 0;

    pid = fork();
    if(pid == 0) {
	printf("[%d] process's pid value : %d\n", getpid(), pid);
	exit(0);
    }
    child = wait(&status);
    printf("[%d] process's pid value : %d\n", getpid(), pid);
    printf("child process [%d] called exit().\n Terminate code : %d, %d\n", child, status>>8, status);
    
    return 0;
}
