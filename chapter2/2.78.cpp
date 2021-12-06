int divide_power2(int x, int k) {
	int w = sizeof(int) << 3;
	int K = k & x >> (w - 1);
    //x为负数bias为 2 ^ k - 1,为正数偏置量bias为0
	int bias = (1 << K) - 1;
	x += bias;
	x >>= k;

	return x;
}