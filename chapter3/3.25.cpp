//汇编等价的C代码
long loop_while2(long a, long b) {
    long ans;

    if(b <= 0) {
        ans = b;
        return ans;
    }

    do {
        ans = b;
        result *= a;
        b -= a;
    } while(b > 0)

    return ans;
}

//转换成题目要求的格式
long loop_while2(long a, long b) {
    long result = b;

    while(b > 0) 
    {
        result = result * a;
        b -= a;
    } 

    return result;
}