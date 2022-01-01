struct ELE {
    long v;
    struct ELE *p;
}

// A.
long fun(struct ELE *ptr) {
    long ans = 0;
    while(ptr) {
       ans = ptr->v;
       ptr += 8;
    }

    return ans;
}

//B.
//累加链表ELE中的所有v值并返回

