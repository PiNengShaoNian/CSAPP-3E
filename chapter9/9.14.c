#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    int fd;
    if((fd = open("hello.txt")) == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if(fstat(fd, &st) == -1) {
        perror("Failed to get file status");
        exit(EXIT_FAILURE);
    }

    char *p;
    if((p = mmap(NULL, st.st_size, PROT_WRITE, MAP_SHARED, fd,0)) == (void *)-1) {
        perror("Failed to mmap");
        exit(EXIT_FAILURE);
    }

    p[0] = 'J';

    return 0;
}