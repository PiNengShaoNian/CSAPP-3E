int divide_power2(int x, int k) {
	int w = sizeof(int) << 3;
	int K = k & x >> (w - 1);
	int bias = (1 << K) - 1;
	x += bias;
	x >>= k;

	return x;
}

int mul3div4(int x) {
	x = (x << 1) + x;

	return divide_power2(x, 2);
}