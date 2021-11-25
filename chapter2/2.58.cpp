int is_little_endian() {
	int a = 1;
	char* p = (char*)&a;

	return p[0];
}

int main() {
	cout << is_little_endian() << endl;
}
