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

int main(int argc, char *argv[]) {
    int clientFd, port, result;
    char *host, inmsg[MAXLINE], outmsg[MAXLINE];
    struct sockaddr_in serverAddr;
    struct hostent *hp;

    if(argc != 3) {
	fprintf(stderr, "사용법 : %s <host> <port> \n", argv[0]);
	exit(1);
    }

    host = argv[1];
    port = atoi(argv[2]);

    clientFd = socket(AF_INET, SOCK_STREAM, 0);

    if((hp = gethostbyname(host)) ==NULL) 
	perror("gethostbyname");

    memset((void *)&serverAddr, 0x00, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = *(u_long *)hp->h_addr_list[0];
    serverAddr.sin_port = htons(port);

    do{
	result = connect(clientFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (result == -1 ) sleep(1);
    }while (result == -1);

    printf("파일 이름 입력 :");
    scanf("%s", inmsg);
    write(clientFd,inmsg,strlen(inmsg)+1);

    read(clientFd, outmsg, MAXLINE);
    printf("%s", outmsg);
    close(clientFd);
    exit(0);
}
