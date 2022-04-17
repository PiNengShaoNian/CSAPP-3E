#include "csapp.h"

int main(int argc, char **argv) {
    struct addrinfo *p, *listp, hints;
    struct sockaddr_in *sockp;
    int rc;

    if(argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    /* Get a list of addrinfo records */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(0);
    }

    /* Print the list of addrinfo records */
    for(p = listp; p != NULL; p = p->ai_next) {
        sockp = (struct sockaddr_in *)p->ai_addr;
        inet_ntop(AF_INET, &sockp->sin_addr, buf, MAXBUF);
        printf("%s\n", buf);
    }

    /* Free the list of addrinfo records */
    freeaddrinfo(listp);
    exit(0);
}