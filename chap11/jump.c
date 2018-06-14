#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

void p1();
void intHandler();
jmp_buf env;

int main() {
    signal(SIGINT, intHandler);

    if(setjmp(env) != 0) {
	printf("인터럽트로 인해 복귀\n");
	exit(0);
    } else printf("처음 통과\n");

    p1();
    return -1;
}

void p1() {
    while(1) {
	printf("루프\n");
	sleep(1);
    }
}

void intHandler() {
    printf("인터럽트 발생\n");
    longjmp(env, 1);
}

