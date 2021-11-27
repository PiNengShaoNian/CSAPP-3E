void copy_int(int val, void* buf, int maxbyptes) {
    //maxbyptes会被转换为无符号数，所以当输入负数是，maxbytes会被
    //解释成大正数
	if (maxbyptes - (int)sizeof(val) >= 0) {
		//memcopy
	}
}