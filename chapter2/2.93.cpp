typedef unsigned float_bits;

float_bits float_absval(float_bits f) {
	unsigned sign = f >> 31;
	unsigned exp = f >> 31 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	int is_nan = (exp == 0xFF && frac != 0);
	if (is_nan) return f;


	return 0 << 31 | exp << 23 | frac;
}