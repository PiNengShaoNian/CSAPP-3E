int main(int argc, char** argv) {
    if(argc != 2) {
        printf("%s usage: <nthreads>\n", argv[0]);
        return;
    }

    int nthreads = atoi(argv[1]);

    pthread_t tid[nthreads];

    for(int i = 0; i < nthreads; i++) {
        if(pthread_create(&tid[i], NULL, thread_main, NULL) != 0) {
            unix_error("pthread_create error");
        }
    }

    for(int i = 0; i < nthreads; i++) {
        if(pthread_join(tid[i], NULL) != 0) {
            unix_error("pthread_join error");
        }
    }

    return 0;
}