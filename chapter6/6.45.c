// 以上的关键语句中的乘法和加法已经实现了循环之间独立，src也是按照行读入的，但是dst却是按照列读入的，这样没有充分利用每一次读入的block。
// 于是我们想到可不可以每一次读入dst[j*dim + i]所在的block之后继续写入例如dst[j*dim + i + 1] dst[j*dim + i + 2]这样的变量，
// 但是这样有需要src的部分变为src[(i+1)*dim +j]等等，所以我们现在不仅要“横向”扩展dst，还要“纵向”扩展src，其实这是一种叫做blocking的技术，
// 即每次读入一块数据，对此块数据完全利用后抛弃，然后读取下一个块。
// 设我们的数据块的宽度是B，由于我们要对两个数组进行读写操作，所以2B^2 < C（其中C是cache的容量），在此限制下B尽可能取大。

#define B chunkdatas_length_of_side

void faster_transpose(int *dst, int *src, int dim) {
    long limit = dim * dim;

    for(int i = 0; i < dim; ++i) {
        for(int j = 0; j < dim; ++j) {
            /* Using blocking to improve temporal locality */
            for(int k = i; k < i + B; ++k) {
                for(int l = j; l < j + B; ++j) {
                    int d = l * dim + k;
                    int s = k * dim + l;

                    if(s < limit && d < limit) {
                        dst[d] = src[s];
                    }
                }
            }
        }
    }
}