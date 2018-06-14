#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int system(const char *cmdstring) {
    int pid, status;

    if (cmdstring == NULL) 
	return 1;

    pid = fork();
    if(pid == -1)
       	return -1;

    if(pid == 0) {
	execl("/bin/sh", "sh", "-c", cmdstring, NULL);
	_exit(127);
    }
    else {
	while(waitpid(pid, &status, 0) < 0)
	    if(errno != EINTR) {
		status = -1;
		break;
	    }
    }
    return(status);
}

int main(int argc, char * argv[]) {
    int status;

    status = system(argv[1]);
    printf("Terminate status : %d\n", status);

    return 0;
}

