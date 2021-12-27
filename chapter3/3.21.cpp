//先将汇编转换成等价的C代码，然后再写成题目要求的格式
//等价C代码
long test(long x, long y) {
    //%rdi = x, %rsi = y
    long ans = 8 * x;
    if(y > 0) {
        ans = y;
        ans -= x;
        long temp = x;
        temp &= y;
        if(x >= y) {
            ans = temp;
        }
    }
    else {
        x += y;
        if(y <= -2) {
            ans = x;
        }
    }

    return ans;
}

//转换成题目要求的格式
long test1(long x, long y) {
    long val = 8 * x;

    if(y > 0) {
        if(x >= y) {
            val = x & y;
        }
        else {
            val = y - x;
        }
    }
    else if(y <= -2) {
         val = x + y;
    }

    return val;
}