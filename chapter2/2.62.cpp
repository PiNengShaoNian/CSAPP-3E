int int_shifts_are_arithemetic() {
	int x = -1;
	//如果是算数右移，那么-1右移一位后还是-1
	return !(x ^ (x >> 1));
}