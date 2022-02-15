void psum1a(float a[], float p[], long n) {
    long i;
    /* last_val holds p[i - 1]; val holds p[i] */
    float last_val,val;
    last_val = p[0] = a[0];

    for(i = 1; i < n; ++i) {
        val = last_val + a[i];
        p[i] = val;
        last_val = val;
    }
}

/* 
  我们引入了局部变量last_val。在迭代i的开始，last_val保存着p[i - 1]的值。
  然后我们计算val为p[i]的值，也是last_val的值。这段代码将last_val存在了局部
  变量中，避免了需要从内存中读出p[i - 1],因而消除psum1中看到的读/写相关
*/