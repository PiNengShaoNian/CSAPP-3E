// arith2:
//   orq %rsi,%rdi
//   sarq %3,%rdi
//   notq %rdi
//   movq %rdx,%rax
//   subq %rdi,%rax
//   ret

long arith2(long x, long y, long z) {
    // %rdi = x, %rsi = y, %rdx = z
    // orq %rsi,%rdi
    long t1 = x | y;
    // sarq %3,%rdi
    long t2 = t1 >> 3;
    // notq %rdi
    long t3 = ~t2;
    // movq %rdx,%rax
    // subq %rdi,%rax
    long t4 = z - t3;
    return t4;
}