typedef unsigned float_bits;

/*
 * 要想实现浮点数*2，可以这么考虑 V = M * 2^E
 * 当浮点数是规格数的时候，我们只需要改变E就行了，E = e - bias ==> 相当于给e的值+1
 * 但是+1有个特殊情况，要是e的位模式为11111110 +1 就需要特殊处理
 * 如果是非规格数， 那么 2^E就是固定的值，我们只能改变M的大小，*2就相当于把小数位左移一位
 */
float_bits float_twice(float_bits f) {
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	//该数字是否为NaN或者无穷
	int is_nan_or_oo = (exp == 0xFF);
	if (is_nan_or_oo) {
		return f;
	}

	//非规格化数偏移量是固定的1 - bias,所以直接将frac部分乘2(也就是左移一位)
	if (exp == 0) {
		frac <<= 1;
	}
	else if (exp == 0xFE) {
		//数字太大用无穷表示
		exp = 0xFF;
		frac = 0;
	}
	else {
		exp += 1;
	}

	return sign << 31 | exp << 23 | frac;
}