//汇编等价的C代码
long fun_b(unsigned long x) {
    long y = 64;
    long ans = 0;

    do {
      ans <<= 1;;
      ans |= (x & 1);
      x >>= 1;
      y -= 1;
    } while(y > 0)

    return ans;
}

//转换为题目要求的格式
long fun_b(unsigned long x) {
    long val = 0;
    long i;
    for(i = 64; i != 0; --y) {
        val = val + val;
        val = (val << 1) | (x & 1);
        x >>= 1;
    }
    return val;
}

//B.这段代码是guarded-do变换生成的，但是编译器发现应为i初始化成了64,所以
//一定会满足测试i不等于0,因此初始测试是没有必要的