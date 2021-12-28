// offset: 0
// label_min: 0
// threshold: 7
// label_max: 7

.L4:
  .quad .L3 0
  .quad .L2 1
  .quad .L5 2
  .quad .L2 3
  .quad .L6 4
  .quad .L7 5
  .quad .L2 6
  .quad .L5 7

void switcher(long a, long b, long c, long *dest) {
    long val;
    switch(a) {
        //有Fall through的只有.L7,对应的标号是5
        case 5: 
          c = b ^ 15;
        //Fall through到.L3,对于的标号是0
        case 0:
          val = 112 + c;
          break;
        //.L2和.L5都对应了多个标号，但是.L2是默认分支
        //所以这里这能选.L5,对于的标号是2和7
        case 2:
        case 7:
          val = (c + b) <<= 2;
          break;
        //只剩下标号4了，对应的情况为.L6
        case 4:
          val = a;
        default:
          val = b;
    }

    *dest = val;
}