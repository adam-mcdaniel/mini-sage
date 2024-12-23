#include <stdint.h>
#include <stddef.h>
#include <string.h>
int64_t mage_as_int(double x) {{ return *(int64_t*)&x; }}

#if __has_include("ffi.h")
#include "ffi.h"
#endif

/* BEGIN PROCEDURES *//* line: 4, column: 0, length: 26 */
int64_t _malloc(int64_t size);
/* line: 5, column: 0, length: 22 */
int64_t _add(int64_t x, int64_t y);
/* line: 6, column: 0, length: 22 */
int64_t _sub(int64_t x, int64_t y);
/* line: 7, column: 0, length: 22 */
int64_t _mul(int64_t x, int64_t y);
/* line: 9, column: 0, length: 23 */
int64_t _div(int64_t x, int64_t y);
/* line: 10, column: 0, length: 21 */
int64_t _eq(int64_t x, int64_t y);
/* line: 12, column: 0, length: 22 */
int64_t _lt(int64_t x, int64_t y);
/* line: 13, column: 0, length: 26 */
int64_t _idx(int64_t ptr, int64_t off);
/* line: 15, column: 0, length: 24 */
int64_t _deref(int64_t ptr);
/* line: 16, column: 0, length: 20 */
int64_t _puts(int64_t s);
/* line: 17, column: 0, length: 22 */
int64_t _putnum(int64_t n);
/* line: 19, column: 0, length: 22 */
int64_t _putc(int64_t ch);
/* line: 20, column: 0, length: 24 */
int64_t _srand(int64_t seed);
/* line: 22, column: 0, length: 32 */
int64_t _rand(int64_t lower, int64_t upper);
/* line: 25, column: 1, length: 43 */
int64_t _putln() {
/* line: 23, column: 13, length: 9 */
_putc(10);
/* line: 24, column: 13, length: 9 */
return 0;
return 0;
}
/* line: 29, column: 1, length: 35 */
int64_t _not(int64_t _x) {
/* line: 28, column: 20, length: 16 */
return _eq(_x, 0);
return 0;
}
/* line: 33, column: 1, length: 43 */
int64_t _neq(int64_t _x, int64_t _y) {
/* line: 32, column: 25, length: 21 */
return _not(_eq(_x, _y));
return 0;
}
/* line: 37, column: 1, length: 93 */
int64_t _mat_get_elem(int64_t _mat, int64_t _rows, int64_t _cols, int64_t _i, int64_t _j) {
/* line: 36, column: 49, length: 45 */
return _deref(_idx(_mat, _add(_mul(_i, _cols), _j)));
return 0;
}
/* line: 42, column: 1, length: 107 */
int64_t _mat_set_elem(int64_t _mat, int64_t _rows, int64_t _cols, int64_t _i, int64_t _j, int64_t _val) {
/* line: 40, column: 42, length: 38 */
*(int64_t*)_idx(_mat, _add(_mul(_i, _cols), _j)) = _val;
/* line: 41, column: 15, length: 11 */
return _val;
return 0;
}
/* line: 71, column: 1, length: 716 */
int64_t _matmul(int64_t _mat_a, int64_t _rows_a, int64_t _cols_a, int64_t _mat_b, int64_t _rows_b, int64_t _cols_b, int64_t _rows_c, int64_t _cols_c) {
/* line: 45, column: 44, length: 40 */
int64_t _mat_c = _malloc(_mul(_rows_a, _cols_b));
/* line: 47, column: 21, length: 17 */
*(int64_t*)_rows_c = _rows_a;
/* line: 48, column: 21, length: 17 */
*(int64_t*)_cols_c = _cols_b;
/* line: 50, column: 27, length: 23 */
_rows_c = _deref(_rows_c);
/* line: 51, column: 27, length: 23 */
_cols_c = _deref(_cols_c);
/* line: 53, column: 14, length: 10 */
int64_t _i = 0;
/* line: 70, column: 4, length: 459 */
while (_lt(_i, _rows_a)) {
/* line: 55, column: 18, length: 10 */
int64_t _j = 0;
/* line: 67, column: 8, length: 382 */
while (_lt(_j, _cols_b)) {
/* line: 57, column: 22, length: 10 */
int64_t _k = 0;
/* line: 58, column: 24, length: 12 */
int64_t _sum = 0;
/* line: 63, column: 12, length: 204 */
while (_lt(_k, _cols_a)) {
/* line: 60, column: 122, length: 106 */
_sum = _add(_sum, _mul(_mat_get_elem(_mat_a, _rows_a, _cols_a, _i, _k), _mat_get_elem(_mat_b, _rows_b, _cols_b, _k, _j)));
/* line: 61, column: 30, length: 14 */
_k = _add(_k, 1);
}
/* line: 63, column: 59, length: 47 */
_mat_set_elem(_mat_c, _rows_c, _cols_c, _i, _j, _sum);
/* line: 64, column: 26, length: 14 */
_j = _add(_j, 1);
}
/* line: 67, column: 22, length: 14 */
_i = _add(_i, 1);
}
/* line: 70, column: 17, length: 13 */
return _mat_c;
return 0;
}
/* line: 86, column: 1, length: 298 */
int64_t _putmat(int64_t _mat, int64_t _rows, int64_t _cols) {
/* line: 74, column: 14, length: 10 */
int64_t _i = 0;
/* line: 85, column: 4, length: 238 */
while (_lt(_i, _rows)) {
/* line: 76, column: 18, length: 10 */
int64_t _j = 0;
/* line: 82, column: 8, length: 146 */
while (_lt(_j, _cols)) {
/* line: 78, column: 56, length: 44 */
_putnum(_mat_get_elem(_mat, _rows, _cols, _i, _j));
/* line: 79, column: 21, length: 9 */
_putc(32);
/* line: 80, column: 26, length: 14 */
_j = _add(_j, 1);
}
/* line: 82, column: 17, length: 9 */
_putc(10);
/* line: 83, column: 22, length: 14 */
_i = _add(_i, 1);
}
/* line: 85, column: 13, length: 9 */
return 0;
return 0;
}
/* line: 102, column: 1, length: 299 */
int64_t _gen_mat(int64_t _rows, int64_t _cols) {
/* line: 89, column: 38, length: 34 */
int64_t _mat = _malloc(_mul(_rows, _cols));
/* line: 91, column: 14, length: 10 */
int64_t _i = 0;
/* line: 101, column: 4, length: 201 */
while (_lt(_i, _rows)) {
/* line: 93, column: 18, length: 10 */
int64_t _j = 0;
/* line: 98, column: 8, length: 126 */
while (_lt(_j, _cols)) {
/* line: 95, column: 58, length: 46 */
*(int64_t*)_idx(_mat, _add(_mul(_i, _cols), _j)) = _rand(0, 10);
/* line: 96, column: 26, length: 14 */
_j = _add(_j, 1);
}
/* line: 98, column: 22, length: 14 */
_i = _add(_i, 1);
}
/* line: 101, column: 15, length: 11 */
return _mat;
return 0;
}
/* line: 123, column: 1, length: 395 */
int64_t _small_test() {
/* line: 106, column: 35, length: 31 */
int64_t _mat_a = (int64_t)(int64_t*)(int64_t[]){ 1, 2, 3, 4, 5, 6 };
/* line: 107, column: 24, length: 20 */
_puts((int64_t)(int64_t*)(int64_t[]){ 4692883206007185741, 2618, 0 });
/* line: 108, column: 24, length: 20 */
_putmat(_mat_a, 2, 3);
/* line: 109, column: 12, length: 8 */
_putln();
/* line: 111, column: 38, length: 34 */
int64_t _mat_b = (int64_t)(int64_t*)(int64_t[]){ 7, 8, 9, 10, 11, 12 };
/* line: 112, column: 24, length: 20 */
_puts((int64_t)(int64_t*)(int64_t[]){ 4764940800045113677, 2618, 0 });
/* line: 113, column: 24, length: 20 */
_putmat(_mat_b, 3, 2);
/* line: 114, column: 12, length: 8 */
_putln();
/* line: 116, column: 19, length: 15 */
int64_t _rows_c = 0;
/* line: 117, column: 19, length: 15 */
int64_t _cols_c = 0;
/* line: 119, column: 67, length: 63 */
int64_t _mat_c = _matmul(_mat_a, 2, 3, _mat_b, 3, 2, ((int64_t)&_rows_c), ((int64_t)&_cols_c));
/* line: 120, column: 24, length: 20 */
_puts((int64_t)(int64_t*)(int64_t[]){ 4836998394083041613, 2618, 0 });
/* line: 121, column: 24, length: 20 */
_putmat(_mat_c, 2, 2);
/* line: 122, column: 12, length: 8 */
_putln();
return 0;
}
/* line: 143, column: 1, length: 381 */
int64_t _big_test(int64_t _n) {
/* line: 126, column: 30, length: 26 */
int64_t _mat_a = _gen_mat(_n, _n);
/* line: 127, column: 24, length: 20 */
_puts((int64_t)(int64_t*)(int64_t[]){ 4692883206007185741, 2618, 0 });
/* line: 128, column: 24, length: 20 */
_putmat(_mat_a, _n, _n);
/* line: 129, column: 12, length: 8 */
_putln();
/* line: 131, column: 30, length: 26 */
int64_t _mat_b = _gen_mat(_n, _n);
/* line: 132, column: 24, length: 20 */
_puts((int64_t)(int64_t*)(int64_t[]){ 4764940800045113677, 2618, 0 });
/* line: 133, column: 24, length: 20 */
_putmat(_mat_b, _n, _n);
/* line: 134, column: 12, length: 8 */
_putln();
/* line: 136, column: 19, length: 15 */
int64_t _rows_c = 0;
/* line: 137, column: 19, length: 15 */
int64_t _cols_c = 0;
/* line: 139, column: 67, length: 63 */
int64_t _mat_c = _matmul(_mat_a, _n, _n, _mat_b, _n, _n, ((int64_t)&_rows_c), ((int64_t)&_cols_c));
/* line: 140, column: 24, length: 20 */
_puts((int64_t)(int64_t*)(int64_t[]){ 4836998394083041613, 2618, 0 });
/* line: 141, column: 24, length: 20 */
_putmat(_mat_c, _n, _n);
/* line: 142, column: 12, length: 8 */
_putln();
return 0;
}
/* line: 151, column: 1, length: 64 */
int64_t _main() {
/* line: 146, column: 14, length: 10 */
_srand(42);
/* line: 148, column: 18, length: 14 */
_big_test(600);
/* line: 150, column: 13, length: 9 */
return 0;
return 0;
}

/* BEGIN MAIN */
int main() {
_main();
}