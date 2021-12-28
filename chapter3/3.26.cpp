//汇编等价的C代码
long fun_a(unsigned long x) {
    long val = 0;
    while(x) {
        val ^= x;
        val >>= 1;
    }

    return val & 0x1;
}

//A.翻译方法
//跳转到中间翻译
