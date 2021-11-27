int saturating_add(int x, int y) {
	int w = sizeof(int) << 3;
	int  TMin = 1 << (w - 1);
	int TMax = TMin - 1;
	int sign_mask_x = x >> (w - 1);
	int sign_mask_y = y >> (w - 1);
	int sum = x + y;
	int sign_mask_sum = sum >> (w - 1);
	int p_s = ~sign_mask_x & ~sign_mask_y & sign_mask_sum;
	int p_n = sign_mask_x & sign_mask_y & ~sign_mask_sum;

	return (p_s & TMax) | (p_n & TMin) | (~(p_s | p_n) & sum);
}