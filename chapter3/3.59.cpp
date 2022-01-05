//汇编等价的C代码
typedef __int128 int128_t;

//这题的主要目标就是用64位的无符号乘法，实现64位的有符号乘法
//并输出一个128位有符号数
//ux * uy乘法产生的结果低64位等于x * y产生的低64位，参考P.67
//所以我们主要关注高64位
//无符号结果的高64位等于ux * uy(高64位) + (Xh * Yl + Yh * Xl)
//这里面Xh,Xl,Yl,YH都是64位的
void store_prod(int128_t *dest, int64_t x, int64_t y) {
    // dest = %rdi, x = %rsi, y = %rdx
    //考虑下面的例子
    //假如寄存器为8位的，x和y也为8位,dest为16位
    //x = 0b11111111 = -1, y = 0b11111100 = -4

    // store_prod:
    //   # %rax = y = 0b11111100
    //   movq %rdx, %rax
    
    //  将y的%rax拓展到%rdx:%rax,现在%rdx所有位都是%rax的符号位
    //  也就是说%rdx = Yh = 0b11111111
    //  cqto                

    // %rcx = x = 0b11111111
    //   movq %rsi, %rcx     # %rcx = x
      
    // 算数右移63位(我们这里用8举例子)，相当把%rcx全部置为
    //  x的符号位，也就是说 %rcx = Xh = 0b11111111 
    //   sarq $63, %rcx

      
    //   %rcx = Yl * Xh = y * 0b11111111
    //                  = 0b00000100(截断只剩下8位)
    //   imulq %rax, %rcx    # %rcx = y * -x_63
      
    //   %rdx = Yh * Xl = 0b11111111 * x 
    //                  = 0b00000001(截断只剩下8位)
    //   imulq %rsi, %rdx    # %rdx = x * -y_63


    //   rcx = Yl * Xh + Yh * Xl = 0b00000101
    //   addq %rdx, %rcx     
      
    //执行ux * uy，将高64位结果存在%rdx,低64位存在%rax
    // ux * uy = 0b11111111 * 0b11111100 
    //         = 255 * 252(解释成无符号)
    //         = 0b1111101100000100
    // %rdx = 0b11111011， %rax = 0b00000100
    //   mulq %rsi           
      
    //%rdx = (ux * uy)的高16位结果 + Yl * Xh + Yh * Xl
    //     = 0b11111011 + 0b00000101
    //     = 0b00000000
    //所以有符号乘法的高8位就存在%rdx中为0b00000000
    //低位就为0b00000100存在%rax中
    //结果就为0b0000000000000100 = 4
    //   addq %rcx, %rdx
      
    //将低位结果存在M[%rdi]
    //将高位结构存储在M[%rdi + 8]
    //   movq %rax, (%rdi) 
    //   movq %rdx, 8(%rdi) 
    //   ret
}