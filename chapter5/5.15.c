void inner6(vec_ptr u, vec_ptr v, data_t *dest) {
    long i;
    long length = vec_length(u);
    long limit = length - 5;

    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum0 = (data_t)0;
    data_t sum1 = (data_t)0;
    data_t sum2 = (data_t)0;
    data_t sum3 = (data_t)0;
    data_t sum4 = (data_t)0;
    data_t sum5 = (data_t)0;

    for(i = 0; i < limit; i += 6) {
        sum0 = sum0 + udata[i] * adata[i];
        sum1 = sum1 + udata[i+1] * adata[i+1];
        sum2 = sum2 + udata[i+2] * adata[i+2];
        sum3 = sum3 + udata[i+3] * adata[i+3];
        sum4 = sum4 + udata[i+4] * adata[i+4];
        sum5 = sum5 + udata[i+5] * adata[i+5];
    }

    for(; i < length; i++) {
        sum0 += udata[i] * adata[i];
    }

    *dest = sum0 + sum1 + sum2 + sum3 + sum4 + sum5;
}