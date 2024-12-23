// A matrix multiplication in mage

extern fun malloc(size);

extern fun add(x, y);
extern fun sub(x, y);
extern fun mul(x, y);
extern fun div(x, y);

extern fun eq(x, y);
extern fun lt(x, y);

extern fun idx(ptr, off);
extern fun deref(ptr);

extern fun puts(s);
extern fun putnum(n);
extern fun putc(ch);

extern fun srand(seed);
extern fun rand(lower, upper);

fun putln() {
    putc(10);
    return 0;
}

fun not(x) {
    return eq(x, 0);
}

fun neq(x, y) {
    return not(eq(x, y));
}

fun mat_get_elem(mat, rows, cols, i, j) {
    return deref(idx(mat, add(mul(i, cols), j)));
}

fun mat_set_elem(mat, rows, cols, i, j, val) {
    *idx(mat, add(mul(i, cols), j)) = val;
    return val;
}

fun matmul(mat_a, rows_a, cols_a, mat_b, rows_b, cols_b, rows_c, cols_c) {
    let mat_c = malloc(mul(rows_a, cols_b));

    *rows_c = rows_a;
    *cols_c = cols_b;

    rows_c = deref(rows_c);
    cols_c = deref(cols_c);

    let i = 0;
    while (lt(i, rows_a)) {
        let j = 0;
        while (lt(j, cols_b)) {
            let k = 0;
            let sum = 0;
            while (lt(k, cols_a)) {
                sum = add(sum, mul(mat_get_elem(mat_a, rows_a, cols_a, i, k), mat_get_elem(mat_b, rows_b, cols_b, k, j)));
                k = add(k, 1);
            }
            mat_set_elem(mat_c, rows_c, cols_c, i, j, sum);
            j = add(j, 1);
        }

        i = add(i, 1);
    }

    return mat_c;
}

fun putmat(mat, rows, cols) {
    let i = 0;
    while (lt(i, rows)) {
        let j = 0;
        while (lt(j, cols)) {
            putnum(mat_get_elem(mat, rows, cols, i, j));
            putc(32);
            j = add(j, 1);
        }
        putc(10);
        i = add(i, 1);
    }
    return 0;
}

fun gen_mat(rows, cols) {
    let mat = malloc(mul(rows, cols));

    let i = 0;
    while (lt(i, rows)) {
        let j = 0;
        while (lt(j, cols)) {
            *idx(mat, add(mul(i, cols), j)) = rand(0, 10);
            j = add(j, 1);
        }
        i = add(i, 1);
    }

    return mat;
}


fun small_test() {
    let mat_a = [1, 2, 3, 4, 5, 6];
    puts("Matrix A:\n");
    putmat(mat_a, 2, 3);
    putln();

    let mat_b = [7, 8, 9, 10, 11, 12];
    puts("Matrix B:\n");
    putmat(mat_b, 3, 2);
    putln();

    let rows_c = 0;
    let cols_c = 0;

    let mat_c = matmul(mat_a, 2, 3, mat_b, 3, 2, &rows_c, &cols_c);
    puts("Matrix C:\n");
    putmat(mat_c, 2, 2);
    putln();
}

fun big_test(n) {
    let mat_a = gen_mat(n, n);
    puts("Matrix A:\n");
    putmat(mat_a, n, n);
    putln();

    let mat_b = gen_mat(n, n);
    puts("Matrix B:\n");
    putmat(mat_b, n, n);
    putln();

    let rows_c = 0;
    let cols_c = 0;

    let mat_c = matmul(mat_a, n, n, mat_b, n, n, &rows_c, &cols_c);
    puts("Matrix C:\n");
    putmat(mat_c, n, n);
    putln();
}

fun main() {
    srand(42);

    big_test(600);

    return 0;
}

main();