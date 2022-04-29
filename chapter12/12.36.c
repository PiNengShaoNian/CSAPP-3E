#include <stdio.h>
#include "csapp.h"

typedef struct { /* Represents a pool of connected descriptors */ //line:conc:echoservers:beginpool
  int maxfd;        /* Largest descriptor in read_set */
  fd_set read_set;  /* Set of all active descriptors */
  fd_set ready_set; /* Subset of descriptors ready for reading  */
  int nready;       /* Number of ready descriptors from select */
  int maxi;         /* Highwater index into client array */
  int clientfd[FD_SETSIZE];    /* Set of active descriptors */
  rio_t clientrio[FD_SETSIZE]; /* Set of active read buffers */
} pool; //line:conc:echoservers:endpool
void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p);
void check_clients(pool *p);


int main(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool;

    if(argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        fprintf(stderr, "use default port 5000\n");
        listenfd = Open_listenfd("5000");
    }
    else {
        listenfd = Open_listenfd(argv[1]);
    }

    init_pool(listenfd, &pool);

    while(1) {
        /* Wait for listening/connected descriptors to become ready */

        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd+1, &pool.ready_set, NULL, NULL, NULL);

        /* If listening descriptor ready, add new client to pool */
        if(FD_ISSET(listenfd, &pool.ready_set)) {
            clientlen = sizeof(clientaddr);
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            add_client(connfd, &pool);
        }

        /* Echo data from ready clients back to them */
        check_clients(&pool);
    }
}