#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

#define TIMEOUT ((unsinged int)5)
#define SIZEOFBUF 1024

jmp_buf buf;

void SIGALRM_handler(int signo) {
    longjmp(buf, 1);
}

char *tfgets(char *s, int size, FILE *stream) {
    if(signal(SIGALRM,SIGALRM_handler) == SIG_ERR) {
        perror("Failed to install SIGALRM_handler");
    }
    else {
        alarm(TIMEOUT);
    }

    if(!setjmp(buf)) {
        return fgets(s,size,stream);
    }
    else { /* longjmp from SIGALRM_handler */
        return NULL;
    }
}

int main(int argc, char const *argv[]) {
    char temp_buffer[SIZEOFBUF];
    char *result = tfgets(temp_buffer, SIZEOFBUF, stdin);

    if(result) {
        printf("Input: %s\n", result);
    }
    else {
        fprintf(stderr, "Time out!\n");
    }

    return 0;
}