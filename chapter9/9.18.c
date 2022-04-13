/* 
                            BLOCK HEADER
      BLOCK SIZE                                       PA/PF    A/F
xxxxxxxxxxxxxxxxxxxxxxxxxxxxx                     x      x       x
PA/PF: Previous Block Allocated/Free
A/F: Allocated/Free
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/* Basic constants and macros */
#define WSIZE       4       /* Word and header/footer size (bytes) */
#define DSIZE       8       /* Doubleword size (bytes) */
#define CHUNKSIZE  (1 << 12)      /* Extend heap by this amount (bytes) */

#define MAX(x, y) ((x) > (y)? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc)  ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p)       (*(unsigned int *)(p))
#define PUT(p, val)  (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)
#define GET_PREVIOUS_ALLOC(p) (GET(p) & 0x2)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)       ((char *)(bp) - WSIZE)
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

/* Global variables */
static char *heap_listp = 0; /* Pointer to first block */
static char *rover; /* Next fit rover */

/* Function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void *coalesce(void *bp);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);

/* mm_init - Initialize the memory manager */
int mm_init() {
    if((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1) {
        return -1;
    }
    PUT(heap_listp, 0); /* Alignment padding */
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); /* Prologue header */
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); /* Prologue footer */
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1)); /* Epilogue header */
    heap_listp += (2 * WSIZE);

    rover = heap_listp;

    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if(extend_heap(CHUNKSIZE / WSIZE) == NULL) {
        return -1;
    }

    return 0;
}

/* mm_malloc - Allocate a block with at least size bytes of payload */
void *mm_malloc(size_t size) {
    size_t asize; /* Adjusted block size */
    size_t extendsize; /* Amount to extend heap if no fit is found */
    char *bp;
    size_t Wsize /* round up to an WSIZE */
    size_t Dsize /* DSIZE after align WSIZE */ 

    if(heap_listp == 0) {
        mm_init();
    }

    /* Ignore spurious requests */
    if(size == 0) {
        return NULL;
    }

    /* Adjust block size to include overhead and alignment reqs. */
    Wsize = (size + (WSIZE - 1)) / WSIZE;
    Dsize = Wsize / 2 + 1;
    asize = Dsize * WSIZE;

    /* Search the free list for a fit */
    if((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize, CHUNKSIZE);
    if((bp = extend_heap(extendsize / WSIZE)) == NULL) {
        return NULL;
    }
    place(bp, asize);
    return bp;
}

/* mm_free - Free a block */
void mm_free(void *bp) {
    if(bp == 0) return;

    size_t size = GET_SIZE(HDRP(bp));

    if(heap_listp == 0) {
        mm_init();
    }

    if(GET_PREVIOUS_ALLOC(HDRP(bp))) {
        PUT(HDRP(bp), PACK(size, 0x2));
    } else {
        PUT(HDRP(bp), PACK(size, 0));
    }
    PUT(FTRP(bp), PACK(size, 0));

    *HDPR(NEXT_BLKP(bp)) &= ~0x2;
    coalesce(bp);
}

/* coalesce - Boundary tag coalescing. Return ptr to coalesced block */
static void *coalesce(void *bp) {
    size_t prev_alloc = GET_PREVIOUS_ALLOC(HDRP(bp));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if(prev_alloc && next_alloc) { /* Case 1 */
        return bp;
    }

    else if(prev_alloc && !next_alloc) { /* Case 2 */
        size += GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0x2));
        PUT(FTRP(bp), PACK(size, 0));
    }

    else if(!prev_alloc && next_alloc) { /* Case 3 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));

        if(GET_PREVIOUS_ALLOC(HDPR(PREV_BLKP(bp)))) {
            PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0x2));
        } else {
            PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        }
        bp = PREV_BLKP(bp);
    }

    else { /* Case 4 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
        if(GET_PREVIOUS_ALLOC(HDPR(PREV_BLKP(bp)))) {
            PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0x2));
        } else {
            PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        }
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    /* Make sure the rover is not pointing into the free block that we just coalesced */
    if(rover > (char *)bp && rover < NEXT_BLKP(bp)) {
        rover = bp;
    }

    return bp;
}

/* mm_realloc - Naive implementation of realloc */
void *mm_realloc(void *ptr, size_t size) {
    size_t oldsize;
    void *newptr;

    /* If size == 0 then this is just free, and we return NULL. */
    if(size == 0) {
        mm_free(ptr);
        return 0;
    }

    /* If oldptr is NULL, then this is just malloc. */
    if(ptr == NULL) {
        return mm_malloc(size);
    }

    newptr = mm_malloc(size);

    /* If realloc() fails the original block is left untouched  */
    if(!newptr) {
        return 0;
    }

    /* Copy the old data. */
    oldsize = GET_SIZE(HDRP(ptr));
    if(size < oldsize) oldsize = size;
    memcpy(newptr, ptr, oldsize);

    /* Free the old block. */
    mm_free(ptr);

    return newptr;
}

/* extend_heap - Extend heap with free block and return its block pointer */
static void *extend_heap(size_t words) {
    char *bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
    if((long)(bp = mem_sbrk(size)) == -1) {
        return NULL;
    }

    if(GET_PREVIOUS_ALLOC(HDRP(bp))) {
        PUT(HDRP(bp), PACK(size, 0x2));
    } else {
        PUT(HDRP(bp), PACK(size, 0));
    }

    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

    /* Coalesce if the previous block was free */
    return coalesce(bp);
}

/* place - Place block of asize bytes at start of free block bp 
           and split if remainder would be at least minimum block size 
*/
static void place(void *bp, size_t asize) {
    size_t csize = GET_SIZE(HDRP(bp));

    if((csize - asize) >= (2 * DSIZE)) {
        if(GET_PREVIOUS_ALLOC(HDPR(bp))) {
            PUT(HDRP(bp), PACK(asize, 0x2 | 0x1));
        } else {
            PUT(HDRP(bp), PACK(asize, 0x1));
        }
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize - asize, 0x2));
        PUT(FTRP(bp), PACK(csize - asize, 0));
    } else {
        if(GET_PREVIOUS_ALLOC(HDPR(bp))) {
            PUT(HDRP(bp), PACK(csize, 0x2 | 0x1));
        } else {
            PUT(HDRP(bp), PACK(csize, 0x1));
        }
        PUT(FTRP(bp), PACK(csize, 1));
        *HDPR(NEXT_BLKP(bp)) |= 0x2;
    }
}

/* find_fit - Find a fit for a block with asize bytes */
static void *find_fit(size_t asize) {
    /* Next fit search */
    char *oldrover = rover;

    /* Search from the rover to the end of list */
    for(; GET_SIZE(HDPR(rover)) > 0; rover = NEXT_BLKP(rover)) {
        if(!GET_ALLOC(HDRP(rover)) && (asize <= GET_SIZE(HDRP(rover)))) {
            return rover;
        }
    }

    /* Search from start of list to the rover */

    for(rover = heap_listp; rover < oldrover; rover = NEXT_BLKP(rover)) {
        if(!GET_ALLOC(HDRP(rover)) && (asize <= GET_SIZE(HDRP(rover)))) {
            return rover;
        }
    }

    return NULL; /* No fit found */
}