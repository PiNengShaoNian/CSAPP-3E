unsigned rotate_left(unsigned x, int n) {
    int w = sizeof(int) << 3;
    //用w - n - 1避免当n为0的时候位移超过31
	return (x << n) | (x >> (w - n - 1) >> 1));
}
