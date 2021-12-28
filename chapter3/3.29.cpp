// for(init-expr; test-expr; update-expr)
//    body-expr

//转换为while

// init-expr;
// while(test-expr) {
//    body-expr
//    update-expr;
// }

//按照上面的规则，转换出来的代码时这样的
// init-expr
long sum = 0;
long i = 0;
// while(test-expr) {
while(i < 10) {
    // body-expr
    if(i & 1) continue;
    sum += i;

    //update-expr
    i++;
}

//A.不难看出，当i=1的时候上面的代码会无限循环

//B.
// init-expr
long sum = 0;
long i = 0;
// while(test-expr) {
while(i < 10) {
    // body-expr
    if(i & 1) {
        goto update;
    }
    sum += i;

    //update-expr
    update: i++;
}