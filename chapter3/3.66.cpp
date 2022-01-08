//将汇编代码转换为等价的C代码
long sum_col(long n, long A[NR(n)][NC(n)], long j) {
    // %r8 = 4 * %rdi + 1
    %r8 = 4 * n + 1
    // %rax = 2 * %rdi + %rdi
    %rax = 3 * n
    // %rdi = %rax
    %rdi = 3 * n
    if(%rax <= 0) {
        %rax = 0;
        return %rax;
    }
    // %r8 = %r8 << 3;
    %r8 = 32 * n + 8;
    // %rcx = 8 * %rdx + %rsi
    %rcx = A + 8 * j
    %rax = 0;
    %rdx = 0; 
    for(;%rdi != %rdx;++%rdx,%rcx += %r8) {
        // %rax = (%rcx)
        %rax += M[%rcx];
    }

    return %rax;
}

如果A的定义为[R][C]
A[i][j]     = A + L * (i * C + j)
            = A + 8 * i * C + 8 * j
A[i + 1][j] = A + L * ((i + 1) * C + j)
            = A + 8 * (i + 1) * C + 8 * j
  A[i + 1][j] - A[i][j]
= 8 * (i + 1) * C - 8 * i * C
= 8 * C
结合上面的for循环的updater语句可以知道
8 * C = %r8 = 32 * n + 8
C = 4 * n + 1
结合for循环的test语句我们可以知道%rdi = R
R = 3 * n

所以C = 4 * n + 1,R = 3 * n
==> NR(n) = 3 * n, NC(n) = 4 * n  + 1