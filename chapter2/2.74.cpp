int tsub_ovf(int x, int y) {
	int k = x + y;
	int w = sizeof(int) << 3;
	x >>= (w - 1);
	y >>= (w - 1);
	k >>= (w - 1);

	return (x != y) && (k == y);
}

int tsub_ok(int x, int y) {
    return !tsub_ovf(x, y);
}