#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    int pid1, pid2, count1= 0, count2 = 0;

    signal(SIGCHLD, SIG_IGN);

    pid1 = fork();
    if(pid1 == 0) {
	while(1) {
	    sleep(1);
	    printf("[%d] 실행 : %d\n", getpid(), ++count1);
	}
    }
    pid2 = fork();
    if(pid2 == 0) {
	while(1) {
	    sleep(1);
	    printf("[%d] 실행 : %d\n", getpid(), ++count2);
	}
    }

    sleep(2);
    kill(pid1, SIGSTOP);
    sleep(2);
    kill(pid1, SIGCONT);
    sleep(2);
    kill(pid2, SIGKILL);
    kill(pid1, SIGKILL);
}
