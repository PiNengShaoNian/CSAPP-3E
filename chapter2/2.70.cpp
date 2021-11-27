int fits_bit(int x, int n) {
    //如果一个数在[-2^n, 2 ^n - 1]范围内
    //则经过n - 1位移后一定全为1(负数)，全为0
	int t = (x >> (n - 1));

	return !t || !~t;
}