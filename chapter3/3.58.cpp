long decode2(long x, long y, long z) {
    // x = %rdi, y= %rsi, z = %rdx
    y -= z;
    x *= y;
    long ans = y;
    ans <<= 63;
    ans >>= 63;
    ans ^= y;
    return ans;
}