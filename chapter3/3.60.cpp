//汇编代码等价的C代码
long loop(long x, int n) {
    long b = 1;
    long result = 0; 
    for(;b != 0;) {
        long d = x;
        d &= b;
        result |= d;
        b <<= (n % 64);
    }
}

//转换为题目要求的格式
long loop(long x, int n) {
    long result = 0;
    long mask;
    for(mask = 1; mask != 0; mask <<= (n % 64)) {
        result |= x & mask
    }

    return result;
}

//A.那个寄存器保存着x,n,result,mask
//  %rdi,%esi,%rax,%rdx

//B.result和mask的初始值是什么？
//  0,1

//C.mask的测试条件是什么？
// mask != 0

//D.mask是如果被更改的
// mask <<= (n % 64)

//E.result是被如何修改的。
//result |= x & mask
