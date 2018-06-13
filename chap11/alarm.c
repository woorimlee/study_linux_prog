/*alarm : 인자로 넘긴 숫자sec 후에 프로세스에 SIGALRM 시그널이 발생되도록 설정한다. 
이전에 설정된 알람이 있으면 취소되고, 그 알람의 남은 초를 반환한다. 따라서 인자가 0이면 이전 알람은 수행되지 않는다. */

#include <stdio.h>
#include <unistd.h>

int main() {
    int sec = 0;
    
    alarm(5);
    while(1) {
	sleep(1);
	printf("%d 초 경과\n", ++sec);
    }

    fprintf(stderr,"실행되지 않음.\n");
    return -1;
}
