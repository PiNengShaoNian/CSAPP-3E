int sumarray3d(int a[N][N][N]) {
    int i, j, k, sum = 0;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = 0; k < N; ++k) {
                sum += a[i][j][k];
            }
        }
    }

    return sum;
}