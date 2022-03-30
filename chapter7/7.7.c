//在bar5.c中声明x的时候使用static，使其成为内部变量
/* bar5.c */
static double x;

void f() {
    x = -0.0;
}