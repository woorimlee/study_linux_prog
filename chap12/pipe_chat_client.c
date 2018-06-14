#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXLINE 256

int main() {
    int fd1, fd2, n;
    char inmsg[MAXLINE];
    
    fd1 = open("./chatfifo1", O_RDONLY);
    fd2 = open("./chatfifo2", O_WRONLY);

    if(fd1 == -1 || fd2 == -1) {
	perror("open");
	exit(1);
    }

    printf("클라이언트 시작\n");
    while(1) {
	memset(inmsg, 0x00, MAXLINE);
	n = read(fd1, inmsg, MAXLINE);
	printf("[서버] -> %s\n", inmsg);
	printf("[클라이언트] : ");
	memset(inmsg, 0x00, MAXLINE);
	fgets(inmsg, MAXLINE, stdin);
	write(fd2, inmsg, strlen(inmsg)+1);
    }
}
