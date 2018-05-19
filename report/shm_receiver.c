#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MEM_SIZE 1024

int main(void) {
    int shm_id;
    void *shm_addr;
    int shm_dt_return;

    if((shm_id = shmget((key_t)4321, MEM_SIZE, IPC_CREAT|0666)) == -1) {
	printf("shmget failed\n");
	return -1;
    }
		        
    printf("shm_id : %d\n", shm_id);

    while(1) { 
	if((shm_addr = shmat(shm_id, (void*)0, 0)) == (void*)-1)
       	{
	    printf("shmat failed\n");
	    return -1;
        }

	
        printf("shm_addr = %p\n", shm_addr);
	printf("%s\n", (char*)shm_addr);

	if(shmdt(shm_addr) == -1) printf("shmdt failed\n");

        sleep(1);
    }

    return 0;
}
