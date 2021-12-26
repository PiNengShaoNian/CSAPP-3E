// void cond(long a, long *p)
// a in %rdi, p in %rsi
// cond:
//   testq %rsi,%rsi   判断是否为空指针如果是就将ZF置为0
//   je .L1            如果ZF为零就跳转到.L1
//   cmpq %rdi,(%rsi)  比较*p和a的值
//   jge .L1           大于等于就跳到.L1
//   movq %rdi,(%rsi)  给*p赋值
// .L1:
//  rep ;ret

void cond(long a, long *p) {
    if(!p) {
        goto noop; 
    }

    if(a <= *p) {
        goto noop;
    }

    *p = a;

    noop: return;
}