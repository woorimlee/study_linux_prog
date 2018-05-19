#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MEM_SIZE 1024

int main(void)
{
    int shm_id;
    void *shm_addr;
    int data = 0;

    srand((unsigned int)time(NULL));

    //int shmget(key_t key, int size, int shmflg); 
    //shmflg : 1) IPC_CREAT,   2) IPC_EXCL
    //allocates a System V shared memory segment
    //On success, a valid shared memory identifier is returned.  On error, -1 is  returned
    if((shm_id = shmget((key_t)4321, MEM_SIZE, IPC_CREAT|0666)) == -1)
    {
	printf("shmget() failed\n");
	return -1;
    }

    printf("shm_id : %d\n", shm_id);

    //void *shmat(int shmid, const void *shmaddr, int shmflg)
    //shmflg : 1) SHM_RDONLY,   2) SHM_RND
    //attaches the System V shared memorysegment 
    //identified by shmid to the address space of the calling process. 
    //The attaching address is specified by shmaddr
    //If shmaddr is NULL, the system chooses a suitable (unused) address at which to attach the segment 
    //On success, shmat() returns the address of the attached shard memory segment,
    //on error, (void *) -1 is returned
    // shm_addr = shmat(shm_id, (void*)0, 0);
    if((shm_addr = shmat(shm_id, (void*)0, 0)) == (void*)-1)
    {
	printf("shared memory failed\n");
	return -1;
    }
    
    printf("shm_addr = %p\n", shm_addr);

    while(1)
    {
	data = rand()%100; 
	sprintf((char*)shm_addr, "%d", data); 
	sleep(1);
	printf("shm_addr : %s\n", (char *)shm_addr);
    }

    return 0;
}
