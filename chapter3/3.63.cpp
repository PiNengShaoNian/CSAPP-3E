long switch_prob(long x, long n) {
    //跳转表
    //[L1, L_Def, L1, L2, L3, L4]

    //label_min - 60 = 0
    //label_min = 60
    //label_max = label_min + 5
    //          = 65

    long result = x;
    switch(n) {
        case 60:
        case 62:
          result = 8 * x;
          break;
        // case 61默认分支
        case 63:
          result = x >> 3;
          break;
        case 64:
          result = (x << 4) - x;
        case 65:
          x *= x;
        default:
          result = x + 0x4B;
    }

    return result;
}