#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_Handler(int signo);

int main() {
    int sec = 0;
    
    signal(SIGALRM, alarm_Handler);
    alarm(5);
    
    while(1) {
	sleep(1);
	printf("%d 초 경과\n", ++sec);
    }
    printf("실행되지 않음\n");
    return -1;
}

void alarm_Handler(int signo) {
    printf("일어나세요\n");
    exit(0);
}

