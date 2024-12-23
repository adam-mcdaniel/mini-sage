#include <math.h>
#include <stdio.h>
#include <stdlib.h>
    
// #define as_int(x) (*(int64_t*)&(x))
// #define as_float(x) (*(double*)&(x))

// Perform a cast from double to int64_t in a way that doesn't violate strict aliasing rules
int64_t as_int(double x) { return *(int64_t*)&x; }
// Perform a cast from int64_t to double in a way that doesn't violate strict aliasing rules
double as_float(int64_t x) { return *(double*)&x; }

int64_t _round(int64_t x) {
    return as_int(round(as_float(x)));
}

int64_t _floor(int64_t x) {
    return as_int(floor(as_float(x)));
}

int64_t _ceil(int64_t x) {
    return as_int(ceil(as_float(x)));
}

int64_t _malloc(int64_t cells) {
    return (int64_t)malloc(cells * sizeof(int64_t));
}

int64_t _to_float(int64_t x) {
    // Convert the int64_t to a double
    return as_int((double)x);
}

int64_t _to_int(int64_t x) {
    // Convert the double to an int64_t
    return (int64_t)as_float(x);
}

int64_t _free(int64_t ptr) {
    free((void*)ptr);
    return 0;
}

int64_t _idx(int64_t ptr, int64_t i) {
    return ptr + i * sizeof(int64_t);
}

int64_t _deref(int64_t x) {
    return *(int64_t*)x;
}

int64_t _debug(int64_t x) {
    printf("DEBUG: int=%lld, float=%f\n", x, as_float(x));
    return x;
}

int64_t _fprint(int64_t x) {
    printf("%lf", as_float(x));
    return x;
}

int64_t _lt(int64_t x, int64_t y) {
    return x < y;
}

int64_t _le(int64_t x, int64_t y) {
    return x <= y;
}

int64_t _gt(int64_t x, int64_t y) {
    return x > y;
}

int64_t _ge(int64_t x, int64_t y) {
    return x >= y;
}

int64_t _eq(int64_t x, int64_t y) {
    return x == y;
}

int64_t _flt(int64_t x, int64_t y) {
    return as_float(x) < as_float(y);
}

int64_t _fgt(int64_t x, int64_t y) {
    return as_float(x) > as_float(y);
}

int64_t _feq(int64_t x, int64_t y) {
    return as_float(x) == as_float(y);
}

int64_t _fadd(int64_t x, int64_t y) {
    return as_int(as_float(x) + as_float(y));
}

int64_t _fsub(int64_t x, int64_t y) {
    return as_int(as_float(x) - as_float(y));
}

int64_t _fmul(int64_t x, int64_t y) {
    return as_int(as_float(x) * as_float(y));
}

int64_t _fdiv(int64_t x, int64_t y) {
    return as_int(as_float(x) / as_float(y));
}

int64_t _frem(int64_t x, int64_t y) {
    return as_int(fmod(as_float(x), as_float(y)));
}

int64_t _fneg(int64_t x) {
    return as_int(-as_float(x));
}

int64_t _add(int64_t x, int64_t y) {
    return x + y;
}

int64_t _sub(int64_t x, int64_t y) {
    return x - y;
}

int64_t _mul(int64_t x, int64_t y) {
    return x * y;
}

int64_t _div(int64_t x, int64_t y) {
    return x / y;
}

int64_t _rem(int64_t x, int64_t y) {
    return x % y;
}

int64_t _neg(int64_t x) {
    return -x;
}

int64_t _put(int64_t x) {
    putchar(x);
    return x;
}

int64_t _putc(int64_t x) {
    putchar(x);
    return x;
}

int64_t _puti(int64_t x) {
    printf("%lld", x);
    return x;
}

int64_t _putf(int64_t x) {
    printf("%f", as_float(x));
    return x;
}

int64_t _putnum(int64_t x) {
    printf("%lld", x);
    return x;
}

int64_t _read() {
    return getchar();
}

int64_t _puts(int64_t ptr) {
    printf("%s", (char*)ptr);
    return 0;
}

int64_t _putsln(int64_t ptr) {
    printf("%s\n", (char*)ptr);
    return 0;
}


int64_t _srand(int64_t x) {
    srand(x);
    return 0;
}

int64_t _rand(int64_t lower, int64_t upper) {
    return (rand() % (upper - lower + 1)) + lower;
}