// 函数          N=64            N=60
// sumA          25%             25%
// sumB          100%            25%
// sumC          50%             25%


#include <stdio.h>

#define SIZEOFCACHE 256
#define SIZEOFBLOCK 4
#define N 60

int main() {
    int cache[SIZEOFCACHE];
    for (int k = 0; k < SIZEOFCACHE; ++k) {
        cache[k] = -1;
    }

    int read = 0;
    int miss = 0;
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            ++read;
            int position = i * N + j;
            int expected_start = position / SIZEOFBLOCK;
            if (cache[expected_start % SIZEOFCACHE] != expected_start) {
                ++miss;
                cache[expected_start % SIZEOFCACHE] = expected_start;
            }
        }
    }

    printf("%g\n", miss / (double)read);

    return 0;
}