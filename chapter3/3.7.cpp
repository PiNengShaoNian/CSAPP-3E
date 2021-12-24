// scale2:
//   leaq (%rdi,%rdi,4),%rax
//   leaq (%rax,%rsi,2),%rax
//   leap (%rax,%rdx,8),%rax

long scale2(long x,long y, long z) {
    //%rdi = x, %rsi = y, %rdx = z, t = %rax
    //leaq (%rdi,%rdi,4),%rax ==>  t = x + 4 * x = 5x
    //leaq (%rax,%rsi,2),%rax ==> t = 5x + 2 * y
    //leap (%rax,%rdx,8),%rax ==> 5x + 2 * y + 8 * z

    return 5 * x + 2 * 6 + 8 * z;
}