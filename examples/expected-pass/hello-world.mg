extern fun malloc(n);
extern fun idx(ptr, i);
extern fun eq(x, y);
extern fun put(x);

let str = malloc(10);
idx(str, 0) = 'H';
idx(str, 1) = 'e';
idx(str, 2) = 'l';
idx(str, 3) = 'l';
idx(str, 4) = 'o';
idx(str, 5) = ' ';
idx(str, 6) = 'W';
idx(str, 7) = 'o';
idx(str, 8) = 'r';
idx(str, 9) = 'l';
idx(str, 10) = 'd';
idx(str, 11) = '!';
idx(str, 12) = '\0';

fun not(x) {
    return eq(x, 0);
}

fun print(s) {
    let i = 0;
    while (not(eq(idx(s, i), 0))) {
        put(idx(s, i));
        i = add(i, 1);
    }
}
