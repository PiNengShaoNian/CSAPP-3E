#include "csapp.h"
#include "csapp.c"
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
    struct stat stat;
    char *type,*readok;
    char buf[MAXBUF];
    char filename[MAXBUF];
    memset(filename,0,MAXBUF);
    memset(buf,0,MAXBUF);

    if(argc != 2) {
        fprintf(stderr, "usage: %s <descriptor number>\n", argv[0]);
    }

    sprintf(buf + sprintf(buf, "/proc/self/fd/"), argv[1]);

    if(readlink(buf, filename, MAXBUF) == -1) {
        fprintf(stderr, "bad file descriptor\n");
        exit(EXIT_FAILURE);
    }

    Stat(filename, &stat);

    if(S_ISREG(stat.st_mode)) {
        type = "regular";
    }
    else if(S_ISDIR(stat.st_mode)) {
        type = "directory";
    }
    else if(S_ISCHR(stat.st_mode)) {
        type = "character special";
    }
    else if(S_ISBLK(stat.st_mode)) {
        type = "block special";
    }
    else if(S_ISFIFO(stat.st_mode)) {
        type = "fifo";
    }
    else if(S_ISLNK(stat.st_mode)) {
        type = "symbolic link";
    }
    else if(S_ISSOCK(stat.st_mode)) {
        type = "socket";
    }
    else {
        type = "unknown";
    }

    if(stat.st_mode & S_IRUSR) {
        readok = "yes";
    }
    else {
        readok = "no";
    }

    printf("type: %s, read: %s\n", type, readok);
    exit(0);
}