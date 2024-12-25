extern fun puti(s);
extern fun puts(s);
extern fun putsln(s);
extern fun putc(s);

let s = "Hello world!";
puti(s);
putc(10);
putsln(s);


extern fun lt(x, y);
extern fun le(x, y);
extern fun sub(x, y);
extern fun idx(a, i);
extern fun deref(p);

fun test(i) {
    puts("Entering test with i = ");
    puti(i);
    putc(10);

    if le(i, 0) {
        return 0;
    }

    let a = [1, 2, 3, 4, 5];

    puts("(before) a[0] = ");
    puti(deref(a));
    putc(10);
    *a = 10;
    puts("(after) a[0] = ");
    puti(deref(a));
    putc(10);
    test(sub(i, 1));

    return 0;
}

test(2);