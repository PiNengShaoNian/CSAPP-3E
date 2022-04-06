#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, const char *argv[], char *env[]) {
    if(execve("/bin/ls", argv, env)) {
        perror("Failed to execve /bin/ls:\n");
    }

    return 0;
}