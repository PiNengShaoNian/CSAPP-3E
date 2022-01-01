struct prob {
    int *p;
    struct {
        int x;
        int y;
    } s;
    struct prob *next;
}

// A.下列字段的偏移量是多少?
// p: 0
// s.x: 8;
// x.y: 12;
// next: 16;

// B.这个结构体总共需要多少字节
//8 + 4 + 4 + 8 = 24

// C.
void sp_init(struct prob *sp) {
    sp->s.x = sp->s.y;
    sp->p = &(sp->s.x);
    sp->next = sp;
}