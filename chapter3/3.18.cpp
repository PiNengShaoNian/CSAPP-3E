// x in %rdi, y in %rsi, z in %rdx
long test(long x, long y, long z) {
    // leaq (%rdi, %rsi), %rax
    // addq %rdx, %rax
    long val = x + y + z;

    //.L2的代码确定在哪之后就知道只用可能从这里能跳转到.L2
    //所以这里跳转对应的汇编代码就是
    //cmpq $-3,%rdi
    //jge .L2
    //这里x大于等于-3就跳.L2,所以x小于-3就进入里面的逻辑
    if(x < -3) {
       //这里的代码分别是.L3和 jpe .L3指令后面的代码，顺序可以互调
       if(y >= z) {
         val = y * z;
       }
       else {
         val = x * y;
       }
    } 
    //不难看出.L4对应的就是最后的return语句
    //只有.L2的代码有可能直接在跳转语句中跳转到return
    //所以只有这里的else if跳转符合条件，因为他一旦不为真
    //就会直接跳转return,其他地方的跳转语句都不会这样，所以
    //就先将.L2标签的代码填到这里
    else if(x > 2){
        val = x  * z;
    }

    return val;
}