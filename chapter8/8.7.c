//只要休眠进程收到一个未被忽略的信号，sleep函数就会提前返回。但是，应为收到一个SIGINT信号的默认行为就是中止进程，
//我们必须设置一个SIGINT的处理函数来允许sleep函数返回。处理程序简单的捕获SIGNAL，并将控制返回给sleep函数，该函数会立即返回。

unsigned int snooze(unsigned int secs) {
    unsigned int rc = sleep(secs);
    printf("Slept for %d of %d secs.\n",secs - rc, secs);

    return rc;
}

void handler(int sig) {
   return;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "usage: %s secs>\n", argv[0]);
        exit(0);
    }

    if(signal(SIGINT,handler) == SIG_ERR) {
        unix_error("signal error\n");
    }

    (void)snooze(atoi(argv[1]));
    exit(0);
}