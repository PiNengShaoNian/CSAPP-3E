#define B size_of_cache_block

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