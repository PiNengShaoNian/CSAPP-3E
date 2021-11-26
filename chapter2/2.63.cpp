#include <bitset>
#include <iostream>
using namespace std;

int srl(int x, int k) {
	unsigned xsra = (int)x >> k;
	unsigned mask = ~(((1 << k) - 1) << (sizeof(int) * 8 - k));

	return xsra & mask;
}

int sra(int x, int k) {
	/* Perform shifr logically */
	int xsrl = (unsigned)x >> k;

	int w = sizeof(int) << 3;
	//前k位全为1
	int mask = (int)-1 << (w - k);
	//符号位为1
	int m = 1 << (w - 1);

	//如果x为正数则!(x & m) - 1为0(所有位都为0)反正为-1(所有位都为1)
	mask &= !(x & m) - 1;

	return xsrl | mask;
}



int main() {
	cout << bitset<sizeof(int) * 8>(srl(-1, 4)) << endl;
	cout << bitset<sizeof(int) * 8>(sra(-1, 4)) << endl;
	cout << bitset<sizeof(int) * 8>(sra(16, 4)) << endl;
}
