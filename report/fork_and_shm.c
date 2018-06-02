#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#define MEM_SIZE 1024
#define NUM_PROC 5

int calculater(int a, char b, int c);

int main(void)
{
    int pid;
    int shm_id;
    int data;
    int result = 0;
    char oper[3] = {'+', '-', '*'};
    int *shm_area;
    void *shm_addr;

    //srand(time(NULL));

    if((shm_id = shmget((key_t)4321, MEM_SIZE, IPC_CREAT|0666)) == -1) 
    {
	fprintf(stderr, "shmget failed\n");
	exit(1);
    } else printf("shmget success\n");

    if((shm_addr = shmat(shm_id, (void *)0, 0)) == (void*)-1)
    {
	fprintf(stderr, "shmat failed\n");
	exit(2);
    } else printf("shmat success\n\n==============\n");

    shm_area = (int *)malloc(sizeof(int)*NUM_PROC);
    shm_area = (int *)shm_addr;

    for (int i = 0; i  < NUM_PROC; i++)
    {
	pid = fork();

	srand(time(NULL));
	if (pid == -1)
       	{
	    fprintf(stderr, "fork failed!\n");
	    exit(1);
	}

	else if (pid == 0) 
	{
	    if (i <= 2)
	    {
		printf("child [%d]'s pid is %d\n", i, getpid());
		data = rand()%100;
		printf("The int num maded by child [%d] is : %d\n", i+1, data);
	    }
	    else 
	    {
		printf("child [%d]'s pid is %d\n", i, getpid());
		data = rand()%3;
		printf("The '%c' operator is maded by child [%d]\n", oper[data], i);
	    }

	    shm_area[i] = data;
	    printf("child [%d] call exit()!!!\n", i);
	    exit(0);
	}
    
	printf("pid : %d\n", pid);
	sleep(1);
    }

//    for(int i = 0; i < NUM_PROC; i++) {
//	wait(NULL);
//	printf("!! Parent got message 'child %d was dead'\n", i);
//    }
    
    wait(NULL);

    printf("\n================\nAll child process was dead.\n");
    printf("The array assigned by 5 child processes is : ");
    for (int i=0; i < NUM_PROC; i++) 
    {
	if (i <=2) printf("%d ", shm_area[i]);
	else printf("%c ", oper[shm_area[i]]);
    } printf("\n\n");


    //shm_area[0] ~ [4] : 20, 50, 90, +, *
    if(shm_area[4] == 2) //Second operator is '*'
    {
	result = calculater(shm_area[1], oper[shm_area[4]], shm_area[2]);
	result = calculater(shm_area[0], oper[shm_area[3]], result);
    } else 
    {
	result = calculater(shm_area[0], oper[shm_area[3]], shm_area[1]);
	result = calculater(result, oper[shm_area[4]], shm_area[2]);
    }

    printf("The result of this program : %d\n\n", result);

    if(shmdt(shm_addr) == -1) printf("shmdt failed\n");
    return 0;
}

int calculater(int a, char b, int c)
{
    int value = 0;

    switch(b) 
    {
	case '+' :
	    value = a + c;
	    return value;
	case '-' :
	    value = a - c;
	    return value;
	case '*' :
	    value = a * c;
	    return value;
    }
}
