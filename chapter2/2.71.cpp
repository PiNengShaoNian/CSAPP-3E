typedef unsigned packed_t;
int xbyte(packed_t word,int bytenum){
	return ((int)word<<(24-(bytenum<<3)))>>24;
}
