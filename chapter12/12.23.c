#include "csapp.h"

typedef struct {
    int maxfd;  /* Larget descriptor currently in read_set */
    fd_set read_set; /* Set of all active descriptors */
    fd_set ready_set; /* Set of descriptors ready for reading */
    int nready; /* Number of ready descriptors from select */
    int maxi; /* Highwater index into client array */
    int clientfd[FD_SETSIZE]; /* Set of active descriptors */
    rio_t clientrio[FD_SETSIZE]; /* Set of active read buffers */
} pool;
void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p);
void check_clients(pool *p);

int byte_cnt = 0; /* Count of total bytes received */

int main(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool;

    if(argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        fprintf(stderr, "use default port 5000 here\n");
        listenfd = Open_listenfd("5000");
    }
    else {
        listenfd = Open_listenfd(argv[1]);
    }

    init_pool(listenfd, &pool);

    while(1) {
        /* Wait for listening/connected descriptors to become ready */
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);

        /* If listening descriptor ready, add new client to pool */
        if(FD_ISSET(listenfd, &pool.ready_set)) {
            clientlen = sizeof(clientaddr);
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            add_client(connfd, &pool);
        }

        /* Echo a text line from each ready connected descriptor */
        check_clients(&pool);
    }
}


void init_pool(int listenfd, pool *p) {
    /* Initially, there are no clients */
    int i;
    /* Initially, listenfd is only in the read set */
    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
    p->maxi = -1;
    for(i = 0; i < FD_SETSIZE; i++) {
        p->clientfd[i] = -1;
    }
}

void add_client(int connfd, pool *p) {
    int i;
    p->nready--;
    for(i = 0; i < FD_SETSIZE; i++) {
        if(p->clientfd[i] < 0) {
            /* Add connected descriptor to pool */
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);

            /* Add the descriptor to the ready set */
            FD_SET(connfd, &p->read_set);

            if(connfd > p->maxfd) {
                p->maxfd = connfd;
            }
            if(i > p->maxi) {
                p->maxi = i;
            }
            break;
        }
    }

    if(i == FD_SETSIZE) {
        fprintf(stderr, "too many clients\n");
        Close(connfd);
    }
}

void check_clients(pool *p) {
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for(i = 0; (i <= p->maxi) && (p->nready > 0); i++) {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        /* If descriptor ready, echo a text line from it */
        if((connfd > 0) && FD_ISSET(connfd, &p->ready_set)) {
            p->nready--;
            if((n = Rio_readlineb(&rio, buf, MAXLINE)) > 0) {
                byte_cnt += n;
                printf("Server received %d (%d total) bytes on fd %d\n", n, byte_cnt, connfd);
                Rio_writen(connfd, buf, n);
            }
            /* EOF Detected, remove descriptor from pool */
            else if(n == 0) {
                Close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
            /* n == -1, it's an error */
            else {
                fprintf(stderr, "error in fd %d, close fd %d connection\n", connfd, connfd);
                Close(connfd);
                p->clientfd[i] = -1;
                FD_CLR(connfd, &p->read_set);
            }
        }
    }
}