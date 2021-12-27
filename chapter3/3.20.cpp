//arith:
//  leaq     7(%rdi), %rax
//  testq    %rdi,%rdi
//  cmovns   %rdi,%rax
//  sqrq     $3,%rax
//  ret

等价的C代码
// long arith(long x) {
//     long ans = 7 + x;
//     if(x >= 0) {
//         ans = x;
//     }

//     ans >>= 3;
//     return ans;
// }

// 转换成题目要求的格式
long arith(long x) {
    return x >= 0 ? (7 + x) / 8 : x / 8;
}

