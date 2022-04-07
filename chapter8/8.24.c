#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

#define N 2

int main() {
    int status;
    pid_t pid;

    for(int i = 0; i < N; ++i) {
        if((pid = fork()) == 0) {
            int *p = 0;
            *p = 0; /* Segmentation fault */

            return 0;
        }
    }

    while((pid = wait(&status)) > 0) {
        if(WIFEXITED(status) != 0) {
            printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status)) {
            fprintf(stderr, "child %d terminated by signal %d\n", pid, WTERMSIG(status));
            psignal(WTERMSIG(status), " ");
        }
        else {
            fprintf(stderr, "child %d terminated abnormally with status information=%d\n", pid, status);
        }
    }

    if(errno != ECHILD) {
        fprintf(stderr, "waitpid error");
    }

    return 0;
}