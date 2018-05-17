/*
  From Stevens Unix Network Programming, vol 1.
  Minor modifications by John Sterling
 */

#include <stdlib.h>         // exit
#include <stdio.h>          // printf, fprintf, stderr
#include <unistd.h>         // read
#include <string.h>         // memset
//#include <strings.h>        // bzero
#include <sys/socket.h>     // socket, AF_INET, SOCK_STREAM
#include <arpa/inet.h>      // inet_pton
#include <netinet/in.h>     // servaddr

#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */
#define PORT 13000

int main(int argc, char **argv) {
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in	servaddr;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <IPaddress>\n", argv[0]);
        exit(1);
    }

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "socket error");
        exit(1);
    }

    //    bzero(&servaddr, sizeof(servaddr));
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(PORT);	/* daytime server */
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        fprintf(stderr, "inet_pton error for: %s\n", argv[1]);
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("connect error");
        exit(1);
    }

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;	/* null terminate */
        if (fputs(recvline, stdout) == EOF) {
            fprintf(stderr, "fputs error");
            exit(1);
        }

    }
    if (n < 0) {
        fprintf(stderr, "read error");
        exit(1);
    }
}
