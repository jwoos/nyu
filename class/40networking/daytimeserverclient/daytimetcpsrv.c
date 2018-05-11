/*
  From Stevens Unix Network Programming, vol 1.
  Minor modifications by John Sterling

  Error chcking ommited for "readability".
 */

#include <stdio.h>       // perror, snprintf
#include <unistd.h>      // close, write
#include <string.h>      // strlen
#include <strings.h>     // bzero
#include <time.h>        // time, ctime
#include <sys/socket.h>  // socket, AF_INET, SOCK_STREAM,
                         // bind, listen, accept
#include <netinet/in.h>  // servaddr, INADDR_ANY, htons

#define	MAXLINE		4096	// max text line length
#define	BUFFSIZE	8192    // buffer size for reads and writes
#define	LISTENQ		1024	// 2nd argument to listen()
#define PORT_NUM        13000

int main(int argc, char **argv) {
    int			listenfd, connfd;  // Unix file descriptors
    struct sockaddr_in	servaddr;          // Note C use of struct
    char		buff[MAXLINE];
    time_t		ticks;

    // 1. Create the socket
    // domain = AF_INET(IPv4); type = SOCK_STREAM, protocol = 0
    listenfd = socket(AF_INET, SOCK_STREAM, 0);


    // 2. Set up the sockaddr_in
    //  zero it.
    //    Note bzero is "deprecated".  Sigh.
    //    bzero(&servaddr, sizeof(servaddr)); 
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;           // Specify the family
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // use any available
    servaddr.sin_port        = htons(PORT_NUM);	  // port to listen on

    // 3. "Bind" that address object to our listening file descriptor
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    // 4. Tell the system that we are going to use this sockect for
    //    listening and request a queue length
    listen(listenfd, LISTENQ);

    for ( ; ; ) {
        // 5. Block until someone connects.
        //    We could provide a sockaddr if we wanted to know details of whom
        //    we are talking to.
        //    Last arg is where to put the size of the sockaddr if
        //    we asked for one
        //        connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);
        connfd = accept(listenfd, NULL, NULL);

        // We had a connection.  Do whatever our task is.
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        int len = strlen(buff);
        if (len != write(connfd, buff, strlen(buff))) {
            perror("write to connection failed");
        }

        // 6. Close the connection with the current client and go back
        //    for another.
        close(connfd);
    }
}
