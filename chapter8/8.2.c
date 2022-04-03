int main() {
    int x = 1;
    if(Fork() == 0) {
        printf("p1: x=%d\n", ++x);
    }
    printf("p2: x=%d\n", --x);
    exit(0);
}

// A. 子进程的输出是什么？
// p1: x=2
// p2: x=1

// B. 父进程的输出是什么？
// p2: x=0