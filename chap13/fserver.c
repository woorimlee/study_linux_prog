#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 100

int main(int argc, char*argv[]) {
    int listenfd, connfd, port, clientlen;
    FILE *fp;
    char inmsg[MAXLINE], outmsg[MAXLINE];
    struct sockaddr_in serveraddr, clientaddr;
    struct hostent *hp;
    char *haddrp;

    signal(SIGCHLD, SIG_IGN);

    if(argc != 2) {
	fprintf(stderr, "사용법: %s <port> \n", argv[0]);
	exit(1);
    }

    port = atoi(argv[1]);

    listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset((void *)&serveraddr, 0x00, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)port);
    bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(listenfd, 5);

    while(1) {
	clientlen = sizeof(clientaddr);
	connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);

	hp = gethostbyaddr((char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
	haddrp = inet_ntoa(clientaddr.sin_addr);
	printf("서버 : %s (%s) %d에 연결됨\n", hp->h_name, haddrp, clientaddr.sin_port);

	if(fork () == 0) {
	    read(connfd, inmsg, MAXLINE);
	    fp = fopen(inmsg, "r");
	    if (fp == NULL) {
		write(connfd, "해당 파일 없음", 10);
	    } 
	    else {
		while(fgets(outmsg, MAXLINE, fp) != NULL) 
		    write(connfd, outmsg, strlen(outmsg)+1);
	    }
	    close(connfd);
	    exit(0);
	}
	else close(connfd);
    }
}
