#include "csapp.h"

/* read line from connfd and echo line to connfd */
int echo_line(int connfd);

void command(void);

int main(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    fd_set read_set, ready_set;

    if(argc != 2) {
        fprintf(stderr, "usage: %s <port> \nuse port 5000 here\n", argv[0]);
        listenfd = Open_listenfd("5000");
    }
    else {
        listenfd = Open_listenfd(argv[1]);
    }

    FD_ZERO(&read_set);
    FD_SET(listenfd, &read_set);
    FD_SET(STDIN_FILENO, &read_set);

    // max n for select
    int n = listenfd + 1;

    while(1) {
        ready_set = read_set;
        Select(n, &ready_set, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &ready_set)) {
            command();
        }

        if(FD_ISSET(listenfd, &ready_set)) {
            clientlen = sizeof(clientaddr);
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            
            if(connfd > FD_SETSIZE) {
                fprintf(stderr, "Too many clients\n");
                Close(connfd);
            }
            FD_SET(connfd, &read_set);
            if(connfd > n) n = connfd + 1;
        }

        // echo one line every time
        int fd;
        for(fd = listenfd + 1; fd < n; fd++) {
            if(FD_ISSET(fd, &ready_set)) {
                if(echo_line(fd) < 0) {
                    Close(fd);
                    FD_CLR(fd, &read_set);
                }
            }
        }
    }

}

void command(void) {
    char buf[MAXLINE];
    if(!Fgets(buf, MAXLINE, stdin)) {
        exit(0);
    }

    printf("%s", buf);
}

int echo_lint(int connfd) {
    ssize_t n;
    char buf[1];

    while((n = Rio_readn(connfd, buf, 1)) > 0) {
        if(buf[0] == '\n') {
            return 0;
        }
        Rio_writen(connfd, buf, 1);
    }

    return -1;
}