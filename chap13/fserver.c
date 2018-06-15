#include <stdio.h>
#include <stdlib.h>
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
    server.sin_port = htons((unsigned short)port);
    bind(listenfd, &serveraddr, sizeof(serveraddr));
    listen(listenfd, 5);

    while(1) {
	clientlen = sizeof(clientaddr);
	connfd = accept(listenfd, &clientaddr, &clientlen);

	hp = gethostbyaddr((
