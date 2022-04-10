static void *find_fit(size_t asize) {
    void *bp;
    
    for(bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if(asize <= GET_SIZE(HDRP(bp))) {
            return bp;
        }
    }

    return NULL;
}