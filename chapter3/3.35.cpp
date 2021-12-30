//汇编等价C代码
long rfun(unsigned long x) {
    long n = x;
    long ans = 0;
    if(x != 0) {
        x >>= 2;
        long res = rfun(x);
        ans += res;
    }



    return ans;
}

//转换成题目的格式
long rfun(unsigned x) {
    if(x == 0) {
        return 0;
    }

    unsigned long nx = x >> 2;
    long rv = rfun(nx);
    return rv + x;
}