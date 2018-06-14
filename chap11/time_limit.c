#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int pid;
void alarmHandler();

int main(int argc, char *argv[]) {
    int status, limit;

    signal(SIGALRM, alarmHandler);
    sscanf(argv[1], "%d", &limit);
    alarm(limit);

    pid = fork();
    if(pid == 0) {
	execvp(argv[2], &argv[2]);
	fprintf(stderr, "%s : 실행 불가\n", argv[2]);
    } else {
	wait(&status);
	printf("[%d]의 자식  프로세스 %d 종료\n", getpid(), pid);
    }
    return -1;
}

void alarmHandler(int signo) {
    printf("자식 프로세스 %d 시간 초과\n", pid);
    exit(0);
    //kill(pid, SIGINT);
}
