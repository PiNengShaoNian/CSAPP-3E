#include <stdio.h>
#include "csapp.h"

#define WRITE_LIMIT 100000
#define PEOPLE 20 // 10 readers, 10 writers
#define N 5

static int readtimes;
static int writetimes;
sem_t mutex;
set_t readercnt;

void *reader(void *vargp) {
    while(1) {
        P(&readercnt);
        P(&mutex);

        readtimes++;

        V(&mutex);
        V(&readercnt);
    }
}

void *writer(void *vargp) {
    while(1) {
        P(&mutex);

        writetimes++;

        if(writetimes == WRITE_LIMIT) {
            printf("%d readers, %d writers\n", readtimes, writetimes);
            exit(0);
        }

        V(&mutex);
    }
}

void init(void) {
    readtimes = 0;
    writetimes = 0;
    Sem_init(&mutex, 0, 1);
    Set_init(&readercnt, 0, N);
}

int main(int argc, char* argv[]) {
    init();
    pthread_t tid[PEOPLE];
    int i;
    for(i = 0; i < PEOPLE; i++) {
        if(i % 2 == 0) {
            Pthread_create(&tid[i], NULL, reader, NULL);
        } else {
            Pthread_create(&tid[i], NULL, writer, NULL);
        }
    }
    
    for(i = 0; i < PEOPLE; i++) {
        Pthread_join(tid[i], NULL);
    }
    return 0;
}