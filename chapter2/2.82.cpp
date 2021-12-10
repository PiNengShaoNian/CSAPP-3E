int x = random();
int y = random();
unsigned ux = (unsigned) x;
unsigned uy = (unsigned) y;

//(A) (x < y) == (-x > -y)
//不成立
//当 x = T_MIN,y = 0是 x < y 为true
// -x还是T_MIN,-y还是0所以-x >-y为false

//(B) ((x + y) << 4) + y - x == 17 * y + 15 * x
//对左移4等价于乘16所以将左边化简得到 (x + y) * 16 + y - x = 17 *y + 15 * x
//所以等式成立

//(C) ~x + ~y + 1 == ~(x + y)
// ~x = -(x + 1) = -x - 1
// ~y = -(y + 1) = -y - 1
// ~(x + y) = -(x + y + 1) = -x - y - 1
// ~x + ~y + 1 = -x - y - 1
//故等式成立

//(D) (ux - uy) == -(unsigned)(y - x)
//unsigned和signed的位级运算没有区别等式成立

//(E) ((x >> 2) << 2) <= x
//右移又左移后会会将低位置零，无论x是负数还是正数都会导致比原来小
//故等式成立