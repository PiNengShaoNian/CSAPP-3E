int fpwr2(int x) {
	/* Result exponent and fraction */
	unsigned exp, frac;
	unsigned u;

	/* 因为2^x 是大于0的，因此我们首先要确定浮点数能够表示的正非规格化数的最小值是
	0 00000000 00000...001  ==> 2 ^ x = 2^-23 * 2^(1-bias) = 2^-23 * 2^(1-(2^7 - 1))
	= 2^-23 * 2^(2-2^7)) = 2^(2 - 2^7 -23)
	= 2 ^ -149
	所以x最小为-149
	*/

	if (x < 2 - pow(2, 7) - 23) {
		/* too small. return 0.0 */
		exp = 0;
		frac = 0;
	}
	else if (x < 2 - pow(2, 7)) {
		/* Denormalized result */
		/* 求出最小的规格化数
		   0 00000001 00000...000
		   E = 1 - 2^7 + 1 = 2 - 2^7 = -126 */

		exp = 0;
		/* 这段代码块求的值应该是非规格化数范围内的值
		   根据 V = M * 2^E V = 2^x  ==> 2^x = M * 2^E
		   frac = M = 2^x / 2^E
		   E = 1 - bias = 2-2^7
		   frac = 2^(x - (2 - 2^7)) 这个是frac的值，但是我们如何获得它的位模式呢？
		   我们知道0 00000000 00000...001 最后边这个1对应的值是2^-23 也就是说
		   小数位的值和他的位模式有一个对应关系，我们只要求出frac是最后这个1（2^-23）的多少
		   倍，然后1 << 这个倍数就可以了，这样就得到了frac的位模式
		 */
		frac = 1 << (unsigned)(x - (2 - pow(2, 7) - 23));
	}
	else if (x < pow(2, 7) - 1 + 1) {
		/* Normalized result */
		/* 11111111 2^8 -1 - (2^7 - 1) ==> 2^8 - 2^7 -1 + 1 ==> 2^7
		   因此求exp 就等于求e e = E + bias = x + (2^7 - 1)
		 */

		exp = pow(2, 7) - 1 + x;
		frac = 0;
	}
	else {
		/* Too big, return +oo */
		exp = 0xFF;
		frac = 0;
	}

	/* pack exp and frac into 32 bits */
	u = exp << 23 | frac;
	/* Result as float */
	return u2f(u);
}