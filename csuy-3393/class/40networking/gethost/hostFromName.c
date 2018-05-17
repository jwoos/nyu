// hostFromName.c

#include <stdio.h>     // puts, NULL
#include <netdb.h>     // getaddrinfo
#include <arpa/inet.h> // inet_ntop
#include <string.h>    // memset

int main(int argc, char* argv[]) {
    char buf[INET_ADDRSTRLEN];
    struct addrinfo* results;

    struct addrinfo hint;

    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_family = AF_INET;

    getaddrinfo(argv[1],
                NULL, // port number of the returned socket addresses will
                      // be left uninitialized
                &hint, // only TCP/IPv4
                &results);
    for (struct addrinfo *rp = results; rp; rp = rp->ai_next) {
        struct sockaddr_in*  p = (struct sockaddr_in*)rp->ai_addr;
        inet_ntop(AF_INET, &p->sin_addr.s_addr, buf, INET_ADDRSTRLEN);
        puts(buf);
    }
    return 0;
}
