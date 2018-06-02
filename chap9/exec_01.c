#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    
    if(fork() == 0) {
	execl("/bin/echo", "echo", "hello", NULL);
	fprintf(stderr, "echo failed\n");
	exit(1);
    }

    if(fork() == 0) {
	execl("/bin/date", "date", NULL);
	fprintf(stderr, "date failed\n");
	exit(2);
    }

    if(fork() == 0) {
	execl("/bin/ls", "ls", "-l", NULL);
	fprintf(stderr, "ls failed\n");
	exit(3);
    }
    
    wait(NULL);
    wait(NULL);
    wait(NULL);
    printf("Parent process end\n");
    return 0;
}

