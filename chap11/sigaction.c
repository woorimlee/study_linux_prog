#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

struct sigaction newact;
struct sigaction oldact;

void sigint_handler(int signo);

int main() {
    newact.sa_handler = sigint_handler;	//sa_handler : 시그널 처리기를 나타내는 필드
					//void *(sa_handler)(int)
    sigfillset(&newact.sa_mask);    //sa_mask : 시그널을 처리하는 동안 차단할 시그널 집합.
				    //sigfillset()으로 시그널 마스크에 포함할 시그널들을 추가하고 초기화.
				    // 현재 모든 시그널을 차단하도록 마스크 된 상태
    sigaction(SIGINT, &newact, &oldact);

    while(1) {
	printf("Ctrl + C를 눌러보세요!\n");
	sleep(1);
    }
    return -1;
}

void sigint_handler(int signo) { 
    printf( "%d번 시그널 처리\n", signo);
    printf("또 누르면 종료됩니다.\n");
    sigaction(SIGINT, &oldact, NULL);
}

