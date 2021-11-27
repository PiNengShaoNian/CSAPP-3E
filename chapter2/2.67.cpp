int int_size_is_32() {
	int set_msb = 1 << 31;
    //超过位宽的位移是未定义行为，可以分两次位移
	int beyond_msb = set_msb << 1;

	return set_msb && !beyond_msb;
}

int int_size_is_32_for_16bit() {
  int set_msb = 1 << 15 << 15 << 1;
  int beyond_msb = set_msb << 1;

  return set_msb && !beyond_msb;
}