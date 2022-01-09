typedef struct {
    int first;
    a_struct a[CNT];
    int last;
} b_struct;

//汇编代码的等价C代码
void test(long i, b_struct *bp) {
    // i in %rdi, bp in %rsi

    // %ecx = *(%rsi + 0x120)
    %ecx = *(bp + 0x120);
    // %ecx = %ecx + *%rsi
    %ecx = *(bp + 0x120) + *bp;
    // %rax = 4 * %rdi + %rdi
    %rax = 5 * i;
    // %rax = 8 *%rax + %rsi
    %rax = 40 * i + bp;
    // %rdx = *(0x8 + %rax);
    %rdx = *(0x8 + 40 * i + bp);
    //将%ecx符号拓展到8，可以知道x中存储的是8字的有符号数
    %rcx = %ecx;
    // *(0x10 + %rax + 8 * %rdx) = %rcx;
    // *(0x10 + 40 * i + bp + 8 * (0x8 + 40 * i + bp)) = *(bp + 0x120) + *bp;
    *(80 + 360 * i + 9 * bp) = *(bp + 0x120) + *bp;
}

//A. CNT的值
//可以看出first的位置为bp,last的位置为bp + 0x120,
//我们可以通过代码中唯一的一次取地址操作`a_struct *ap = &bp->a[i]`
//知道他对于的汇编代码为`lea (%rsi,%rax,8),%rax; mov 0x8(%rax),%rdx`,所以可以知道
// &bp->a[i] = 0x8 + 40 * i + bp，移除掉偏移量，我们可以通过
//40 * i可以知道bp->a数组中存储的元素(也就是a_struct)大小为40
//通过偏移量0x8 + bp我们可以知道数组a的存储范围为[0x8,0x120]也就是
//280个字节所以CNT = 280 / 40 = 7

//B. 结构体a_struct的完整声明，假设这个结构中只有idx和x，并且他们中
//保存的都是有符号值。
//从最后一行汇编代码可以看出ap->idx这个取指针当作索引对于的汇编的代码就是
//`mov 0x8(%rax),%rdx # %rdx = *(0x8 + 40 * i + bp)`
// 从最后*(0x10 + %rax + 8 * %rdx) = %rcx可以看出%rdx对应数组ap->x的索引
//所以8就是数组元素的大小那么0x10 + %rax就是ap->x数组的偏移量，
// 可见%rax + 0x8 --> ap->idx,%rax + 0x10 --> ap->x
// ap的存储区域等于 [%rax + 0x8,%rax + 0x8 + ap元素的大小]
//也就是[%rax + 8, %rax + 48],
// ap->x的区域为[%rax + 16,%rax + 48]，应为x中存储的元素为8
//所以x的长度为4，所以他的声明因该是这样的(注意十六进制和十进制之间的转换)
typedef struct {
    long idx;
    long x[4];
} a_struct;  