// A. 优化版版运行起来很像下面的C代码

/* Make sure dest updated on each iteration */
void combine3w(vec_ptr v, data_t *dest) {
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    /* Initialize in event length <= 0 */
    *dest = acc;
    
    for(i = 0; i < length; i++) {
        acc = acc OP data[i];
        *dest = acc;
    }
}
//可以看到原来一个循环需要两次读一次写，优化后的只需要一次读，一次写

// B. combine3的两个版本有相同的功能，甚至于相同的内存别名使用

// C. 这个变换可以不改变程序的行为，因为，除了第一次迭代外，每次迭代开始
//    时从dest读出的值和前一次迭代最后写入到这个寄存器的值是相同的。因此
//    合并指令可以简单的使用在循环开始时就已经在%xmm0中的值。