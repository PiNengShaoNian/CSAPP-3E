unsigned replace_byte(unsigned x, int i, unsigned char b) {
	return ((~(0xff << (i << 3)) & x) | (b << (i << 3)));
}


int main() {
	cout << hex << replace_byte(0x12345678, 2, 0xab) << " " << replace_byte(0x12345678, 0, 0xab) << endl;
}
