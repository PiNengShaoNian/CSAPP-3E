int any_odd_one(unsigned x) {
	return !!(0x55555555 & x);
}