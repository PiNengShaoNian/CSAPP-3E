static void place(void *bp, size_t asize) {
    size_t csize = GET_SIZE(HDPR(bp));
    size_t bsize = csize - asize;
    if(bsize >= (2 * DSIZE)) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(bsize, 0));
        PUT(FTRP(bp), PACK(bsize, 0));
    }
    else {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}