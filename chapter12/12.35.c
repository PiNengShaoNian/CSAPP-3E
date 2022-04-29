#include "csapp.h"

/*
 * doit - handle one HTTP request/response transaction
 */
void doit(int fd);

int main(int argc, char **argv) {
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    /* Check command line args */
    if(argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        fprintf(stderr, "use default port 5000\n");
        listenfd = Open_listenfd("5000");
    }
    else {
        listenfd = Open_listenfd(argv[1]);
    }

    while(1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);

        if(Fork() == 0) {
            Close(listenfd);
            doit(connfd);
            Close(connfd);
            exit(0);
        }

        Close(connfd);
    }
}
