#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int x = 0;
//이 c 파일에서만 사용하는 전역변수
static pthread_mutex_t the_mutex = PTHREAD_MUTEX_INITIALIZER;

void * start_thread(void *message);

int main(void) {
    pthread_t t1, t2;

    const char *message1 = "Thing 1";
    const char *message2 = "Thing 2";
    
    pthread_create(&t1, NULL, start_thread, (void *) message1);
    pthread_create(&t2, NULL, start_thread, (void *) message2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

void * start_thread (void *message) {
    int t;
    for( ;; ) {
        pthread_mutex_lock(&the_mutex);
    	printf("%s : %d\n", (const char *)message, x);
	sleep(1);
	x++;
        pthread_mutex_unlock(&the_mutex);
    }
    
}
