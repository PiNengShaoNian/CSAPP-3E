#include "csapp.h"

int main(int argc, char **argv) {
    struct in_addr inaddr;
    int rc;

    if(argc != 2) {
        fprintf(stderr, "usage: %s <dotted_decimal_ip_addr>\n", argv[0]);
        exit(0);
    }

    rc = inet_pton(AF_INET, argv[1], &inaddr);

    if(rc == 0) {
        fprintf(stderr, "inet_pton error for %s\n", argv[1]);
        exit(0);
    }
    else if(rc < 0) {
        fprintf(stderr, "inet_pton error\n");
        exit(0);
    }

    printf("0x%x\n", ntohl(inaddr.s_addr));
    exit(0);
}