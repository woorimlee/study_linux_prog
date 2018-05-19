#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int pid;
    int i = 0;

    pid = fork();

    if (pid ==-1) {
	printf("fork failed\n");
	return -1;
    }

    else if (pid == 0) {
	printf("Child pid is %d\n", getpid());
	
	while(1) {
	    printf("Child -> %d\n", i);
	    i++;
	    sleep(1);
	}
    }

    else {
	printf("Parents : My child PID is %d, My pid is %d\n", pid, getpid());
	while(1) {
	    printf("Parents -> %d\n", i);
	    i+= 4;
	    sleep(1);
	}
    }

    return 0;
}
