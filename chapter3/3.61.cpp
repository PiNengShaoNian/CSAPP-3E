//对于jle这样的跳转指令。
//使用了流水线的CPU，这样的跳转是存在隐患的（P145），
//分支预测失败就会刷新掉所有流水线中取到而未执行的指令，影响运行性能。
long cread_alt(long *xp) {
    long t = 1;
    long *p = xp ? xp : &t;

    return *p;
}