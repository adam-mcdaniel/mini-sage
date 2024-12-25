extern fun malloc(n);
extern fun idx(ptr, i);
extern fun eq(x, y);
extern fun putc(x);
extern fun putp(x);
extern fun puti(x);
extern fun deref(x);
extern fun add(x, y);
extern fun sub(x, y);
extern fun neg(x) {
    return sub(0, x);
}

fun newline() {
    putc('\n');
}

fun inc(x) {
    *x = add(deref(x), 1);
}

fun dec(x) {
    *x = sub(deref(x), 1);
}

let str = malloc(20);
idx(str, 0) = 'H';
idx(str, 1) = 'e';
idx(str, 2) = 'l';
idx(str, 3) = 'l';
idx(str, 4) = 'o';
idx(str, 5) = ' ';
idx(str, 6) = 'w';
idx(str, 7) = 'o';
idx(str, 8) = 'r';
idx(str, 9) = 'l';
idx(str, 10) = 'd';
idx(str, 11) = '!';
idx(str, 12) = 0;

fun not(x) {
    return eq(x, 0);
}

fun print(s) {
    let i = 0;
    while (not(eq(deref(idx(s, i)), 0))) {
        putc(deref(idx(s, i)));
        i = add(i, 1);
    }
}

print(str);