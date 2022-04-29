#include <stdio.h>
#include "csapp.h"

#define N 640
#define M 640

#define THREAD (1<<4)
#define ROWS_PER_THREAD (N / THREAD)

int M1[N][M];
int M2[N][M];

int MUL12[N][M] = {0};

void non_concurrent_mul(void) {
    int i, j, k;

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            int sum = 0;
            for(k = 0; k < N; k++) {
                sum += M1[i][k] * M2[k][j];
            }
            MUL12[i][j] = sum;
        }
    }
}

void *thread_mul(void *vargp) {
    int idx = *(int *)vargp;
    int i, j, k;
    int start = ROWS_PER_THREAD * idx;
    for(i = start; i < start + ROWS_PER_THREAD; i++) {
        for(j = 0; j < N; j++) {
            int sum = 0;
            for(k = 0; k < N; k++) {
                sum += M1[i][k] * M2[k][j];
            }
            MUL12[i][j] = sum;
        }
    }
}

void concurrent_mul(void) {
    int i;
    pthread_t tid[THREAD];
    int idx[THREAD];

    for(i = 0; i < THREAD; i++) {
        idx[i] = i;
        Pthread_create(&tid[i], NULL, thread_mul, (void *)&idx[i]);
    }

    for(i = 0; i < THREAD; i++) {
        Pthread_join(tid[i], NULL);
    }
}