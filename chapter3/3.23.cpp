//先将汇编转换成等价的C代码
long dw_loop(long x) {
    //movq %rdi, %rax
    long ans = x;
    //movq %rdi, %rcx 
    //imulq %rdi, %rcx
    long y = x * x;
    //leaq   (%rdi, %rdi), %rdx
    long z = 2 * x;

    do {
        //leaq   1(%rcx, %rax), %rax 
        ans = 1 + y + ans;
        //subq   $1, %rdx  
        z--;

        // testq  %rdx, %rdx            # Test n   
        //jg     .L2
    } while(z > 0)

    return ans;
}


//A. 哪些寄存器用来存放程序值 x、y 和 n ？
//x = %rdi,y = %rcx, n = %rdx

// B. 编译器如何消除对指针变量 p 和表达式 (*p)++ 隐含的指针间接引用的需求？
//编译器认为指针 p 总是指向 x ，因此表达式 (*p)++ 
//就能够实现 x 加一。代码通过 leaq 指令，把这个加一和加 y 组合起来。