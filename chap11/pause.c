#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void int_Handler(int signo);

int main() {
    signal(SIGINT, int_Handler);

    pause();

    printf("실행되지 않음\n");

    return -1;
}

void int_Handler(int signo) {
    printf("\n인터럽트 시그널 처리\n시그널 번호 :%d\n", signo);
    exit(0);
}
