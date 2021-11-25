int main() {
	cout << hex << ((0x89abcdef & 0xff) | (0x76543210 & ~0xff)) << endl;
}
