#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int status;
    if((status = system("date")) < 0)
	perror("system() error\n");
    printf("Terminate code %d\n", WEXITSTATUS(status));


    if((status = system("eoroewjrlwaroewar")) < 0)
            perror("system() error\n");
    printf("Terminate code %d\n", WEXITSTATUS(status));


    if((status = system("who; exit 44")) < 0)
	perror("system() error\n");
    printf("Terminate code %d\n", WEXITSTATUS(status));
}

