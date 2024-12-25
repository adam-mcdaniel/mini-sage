#include <stdint.h>
#include <stddef.h>
#include <string.h>
int64_t mage_as_int(double x) {{ return *(int64_t*)&x; }}

#if __has_include("ffi.h")
#include "ffi.h"
#endif

/* BEGIN PROCEDURES *//* line: 167, column: 51, length: 25 */
int64_t _malloc(int64_t size);
/* line: 168, column: 13, length: 26 */
int64_t _idx(int64_t ptr, int64_t off);
/* line: 168, column: 38, length: 25 */
int64_t _deref(int64_t ptr);
/* line: 169, column: 4, length: 20 */
int64_t _puts(int64_t s);
/* line: 169, column: 29, length: 25 */
int64_t _puti(int64_t n);
/* line: 170, column: 0, length: 25 */
int64_t _putf(int64_t f);
/* line: 170, column: 24, length: 24 */
int64_t _putc(int64_t ch);
/* line: 170, column: 49, length: 25 */
int64_t _add(int64_t x, int64_t y);
/* line: 171, column: 20, length: 25 */
int64_t _sub(int64_t x, int64_t y);
/* line: 171, column: 45, length: 25 */
int64_t _mul(int64_t x, int64_t y);
/* line: 173, column: 16, length: 26 */
int64_t _div(int64_t x, int64_t y);
/* line: 174, column: 18, length: 25 */
int64_t _eq(int64_t x, int64_t y);
/* line: 175, column: 18, length: 27 */
int64_t _lt(int64_t x, int64_t y);
/* line: 177, column: 15, length: 25 */
int64_t _fadd(int64_t a, int64_t b);
/* line: 178, column: 15, length: 25 */
int64_t _fsub(int64_t a, int64_t b);
/* line: 178, column: 40, length: 25 */
int64_t _fmul(int64_t a, int64_t b);
/* line: 180, column: 20, length: 26 */
int64_t _fdiv(int64_t a, int64_t b);
/* line: 180, column: 45, length: 25 */
int64_t _feq(int64_t a, int64_t b);
/* line: 181, column: 17, length: 27 */
int64_t _flt(int64_t a, int64_t b);
/* line: 182, column: 18, length: 25 */
int64_t _to_float(int64_t i);
/* line: 183, column: 9, length: 26 */
int64_t _to_int(int64_t f);
/* line: 187, column: 1, length: 43 */
int64_t _putln() {
/* line: 184, column: 11, length: 9 */
_putc(10);
/* line: 186, column: 0, length: 9 */
return 0;
return 0;
}
/* line: 187, column: 38, length: 35 */
int64_t _not(int64_t _x) {
/* line: 187, column: 36, length: 16 */
return _eq(_x, 0);
return 0;
}
/* line: 188, column: 38, length: 43 */
int64_t _neq(int64_t _x, int64_t _y) {
/* line: 188, column: 36, length: 21 */
return _not(_eq(_x, _y));
return 0;
}
/* line: 189, column: 18, length: 44 */
int64_t _fzero() {
/* line: 189, column: 16, length: 19 */
return _to_float(0);
return 0;
}
/* line: 191, column: 12, length: 43 */
int64_t _fone() {
/* line: 191, column: 10, length: 19 */
return _to_float(1);
return 0;
}
/* line: 194, column: 37, length: 115 */
int64_t _ftiny() {
/* line: 192, column: 11, length: 17 */
int64_t _one = _fone();
/* line: 194, column: 4, length: 32 */
int64_t _million = _to_float(1000000);
/* line: 194, column: 35, length: 26 */
return _fdiv(_one, _million);
return 0;
}
/* line: 196, column: 14, length: 109 */
int64_t _fpoint01() {
/* line: 195, column: 15, length: 17 */
int64_t _one = _fone();
/* line: 195, column: 48, length: 28 */
int64_t _hundred = _to_float(100);
/* line: 196, column: 12, length: 26 */
return _fdiv(_one, _hundred);
return 0;
}
/* line: 203, column: 2, length: 124 */
int64_t _body_get_x(int64_t _bodies, int64_t _nbodies, int64_t _stride, int64_t _i) {
/* line: 199, column: 28, length: 33 */
int64_t _off = _add(_mul(_i, _stride), 0);
/* line: 201, column: 16, length: 31 */
return _deref(_idx(_bodies, _off));
return 0;
}
/* line: 208, column: 3, length: 123 */
int64_t _body_get_y(int64_t _bodies, int64_t _nbodies, int64_t _stride, int64_t _i) {
/* line: 206, column: 59, length: 33 */
int64_t _off = _add(_mul(_i, _stride), 1);
/* line: 207, column: 18, length: 31 */
return _deref(_idx(_bodies, _off));
return 0;
}
/* line: 211, column: 32, length: 124 */
int64_t _body_get_vx(int64_t _bodies, int64_t _nbodies, int64_t _stride, int64_t _i) {
/* line: 209, column: 27, length: 33 */
int64_t _off = _add(_mul(_i, _stride), 2);
/* line: 211, column: 27, length: 31 */
return _deref(_idx(_bodies, _off));
return 0;
}
/* line: 215, column: 36, length: 124 */
int64_t _body_get_vy(int64_t _bodies, int64_t _nbodies, int64_t _stride, int64_t _i) {
/* line: 214, column: 21, length: 33 */
int64_t _off = _add(_mul(_i, _stride), 3);
/* line: 215, column: 31, length: 31 */
return _deref(_idx(_bodies, _off));
return 0;
}
/* line: 217, column: 35, length: 123 */
int64_t _body_get_m(int64_t _bodies, int64_t _nbodies, int64_t _stride, int64_t _i) {
/* line: 216, column: 43, length: 33 */
int64_t _off = _add(_mul(_i, _stride), 4);
/* line: 217, column: 30, length: 31 */
return _deref(_idx(_bodies, _off));
return 0;
}
/* line: 220, column: 25, length: 136 */
int64_t _body_set_x(int64_t _bodies, int64_t _nbodies, int64_t _stride, int64_t _i, int64_t _val) {
/* line: 218, column: 43, length: 33 */
int64_t _off = _add(_mul(_i, _stride), 0);
/* line: 220, column: 5, length: 24 */
*(int64_t*)_idx(_bodies, _off) = _val;
/* line: 220, column: 23, length: 11 */
return _val;
return 0;
}
/* line: 225, column: 26, length: 134 */
int64_t _body_set_y(int64_t _bodies, int64_t _nbodies, int64_t _stride, int64_t _i, int64_t _val) {
/* line: 223, column: 22, length: 33 */
int64_t _off = _add(_mul(_i, _stride), 1);
/* line: 225, column: 8, length: 24 */
*(int64_t*)_idx(_bodies, _off) = _val;
/* line: 225, column: 24, length: 11 */
return _val;
return 0;
}
/* line: 231, column: 25, length: 135 */
int64_t _body_set_vx(int64_t _bodies, int64_t _nbodies, int64_t _stride, int64_t _i, int64_t _val) {
/* line: 228, column: 8, length: 33 */
int64_t _off = _add(_mul(_i, _stride), 2);
/* line: 231, column: 7, length: 24 */
*(int64_t*)_idx(_bodies, _off) = _val;
/* line: 231, column: 23, length: 11 */
return _val;
return 0;
}
/* line: 236, column: 10, length: 135 */
int64_t _body_set_vy(int64_t _bodies, int64_t _nbodies, int64_t _stride, int64_t _i, int64_t _val) {
/* line: 234, column: 15, length: 33 */
int64_t _off = _add(_mul(_i, _stride), 3);
/* line: 235, column: 25, length: 24 */
*(int64_t*)_idx(_bodies, _off) = _val;
/* line: 236, column: 8, length: 11 */
return _val;
return 0;
}
/* line: 238, column: 50, length: 134 */
int64_t _body_set_m(int64_t _bodies, int64_t _nbodies, int64_t _stride, int64_t _i, int64_t _val) {
/* line: 238, column: 3, length: 33 */
int64_t _off = _add(_mul(_i, _stride), 4);
/* line: 238, column: 32, length: 24 */
*(int64_t*)_idx(_bodies, _off) = _val;
/* line: 238, column: 48, length: 11 */
return _val;
return 0;
}
/* line: 239, column: 35, length: 41 */
int64_t _fsquare(int64_t _x) {
/* line: 239, column: 33, length: 18 */
return _fmul(_x, _x);
return 0;
}
/* line: 263, column: 51, length: 812 */
int64_t _calc_force(int64_t _bodies, int64_t _nbodies, int64_t _stride, int64_t _i, int64_t _j, int64_t _out_fx, int64_t _out_fy) {
/* line: 244, column: 1, length: 49 */
int64_t _xi = _body_get_x(_bodies, _nbodies, _stride, _i);
/* line: 244, column: 57, length: 49 */
int64_t _yi = _body_get_y(_bodies, _nbodies, _stride, _i);
/* line: 245, column: 34, length: 49 */
int64_t _xj = _body_get_x(_bodies, _nbodies, _stride, _j);
/* line: 247, column: 10, length: 49 */
int64_t _yj = _body_get_y(_bodies, _nbodies, _stride, _j);
/* line: 248, column: 16, length: 49 */
int64_t _mj = _body_get_m(_bodies, _nbodies, _stride, _j);
/* line: 248, column: 49, length: 22 */
int64_t _dx = _fsub(_xj, _xi);
/* line: 249, column: 17, length: 22 */
int64_t _dy = _fsub(_yj, _yi);
/* line: 251, column: 8, length: 40 */
int64_t _r2 = _fadd(_fsquare(_dx), _fsquare(_dy));
/* line: 252, column: 8, length: 19 */
int64_t _tiny = _ftiny();
/* line: 253, column: 26, length: 66 */
if (_flt(_r2, _tiny)) {
/* line: 252, column: 57, length: 10 */
_r2 = _tiny;
} else {

}
/* line: 253, column: 49, length: 23 */
int64_t _float_one = _fone();
/* line: 255, column: 11, length: 29 */
int64_t _r2r2 = _fmul(_r2, _r2);
/* line: 258, column: 1, length: 38 */
int64_t _inv_r3 = _fdiv(_float_one, _r2r2);
/* line: 260, column: 46, length: 36 */
int64_t _fx = _fmul(_mj, _fmul(_dx, _inv_r3));
/* line: 262, column: 20, length: 36 */
int64_t _fy = _fmul(_mj, _fmul(_dy, _inv_r3));
/* line: 263, column: 15, length: 13 */
*(int64_t*)_out_fx = _fx;
/* line: 263, column: 33, length: 13 */
*(int64_t*)_out_fy = _fy;
/* line: 263, column: 48, length: 9 */
return 0;
return 0;
}
/* line: 334, column: 0, length: 2152 */
int64_t _update_bodies(int64_t _bodies, int64_t _nbodies, int64_t _stride, int64_t _dt) {
/* line: 265, column: 30, length: 37 */
int64_t _forces = _malloc(_mul(_nbodies, 2));
/* line: 265, column: 52, length: 10 */
int64_t _i = 0;
/* line: 266, column: 17, length: 18 */
int64_t _f0_ = _fzero();
/* line: 270, column: 11, length: 176 */
while (_lt(_i, _nbodies)) {
/* line: 267, column: 44, length: 38 */
*(int64_t*)_idx(_forces, _add(_mul(_i, 2), 0)) = _f0_;
/* line: 269, column: 40, length: 38 */
*(int64_t*)_idx(_forces, _add(_mul(_i, 2), 1)) = _f0_;
/* line: 269, column: 63, length: 14 */
_i = _add(_i, 1);
}
/* line: 270, column: 17, length: 6 */
_i = 0;
/* line: 298, column: 24, length: 801 */
while (_lt(_i, _nbodies)) {
/* line: 272, column: 7, length: 10 */
int64_t _j = 0;
/* line: 297, column: 70, length: 718 */
while (_lt(_j, _nbodies)) {
/* line: 297, column: 37, length: 648 */
if (_neq(_i, _j)) {
/* line: 277, column: 13, length: 24 */
int64_t _fx_addr = _malloc(1);
/* line: 278, column: 11, length: 24 */
int64_t _fy_addr = _malloc(1);
/* line: 281, column: 13, length: 60 */
_calc_force(_bodies, _nbodies, _stride, _i, _j, _fx_addr, _fy_addr);
/* line: 283, column: 20, length: 51 */
int64_t _cur_fx = _deref(_idx(_forces, _add(_mul(_i, 2), 0)));
/* line: 286, column: 13, length: 51 */
int64_t _cur_fy = _deref(_idx(_forces, _add(_mul(_i, 2), 1)));
/* line: 287, column: 34, length: 42 */
int64_t _new_fx = _fadd(_cur_fx, _deref(_fx_addr));
/* line: 288, column: 36, length: 42 */
int64_t _new_fy = _fadd(_cur_fy, _deref(_fy_addr));
/* line: 290, column: 0, length: 41 */
*(int64_t*)_idx(_forces, _add(_mul(_i, 2), 0)) = _new_fx;
/* line: 297, column: 10, length: 41 */
*(int64_t*)_idx(_forces, _add(_mul(_i, 2), 1)) = _new_fy;
} else {

}
/* line: 297, column: 51, length: 14 */
_j = _add(_j, 1);
}
/* line: 298, column: 7, length: 14 */
_i = _add(_i, 1);
}
/* line: 298, column: 30, length: 6 */
_i = 0;
/* line: 332, column: 5, length: 995 */
while (_lt(_i, _nbodies)) {
/* line: 299, column: 52, length: 50 */
int64_t _m = _body_get_m(_bodies, _nbodies, _stride, _i);
/* line: 300, column: 46, length: 50 */
int64_t _vx = _body_get_vx(_bodies, _nbodies, _stride, _i);
/* line: 301, column: 30, length: 50 */
int64_t _vy = _body_get_vy(_bodies, _nbodies, _stride, _i);
/* line: 302, column: 12, length: 50 */
int64_t _x = _body_get_x(_bodies, _nbodies, _stride, _i);
/* line: 304, column: 12, length: 50 */
int64_t _y = _body_get_y(_bodies, _nbodies, _stride, _i);
/* line: 307, column: 0, length: 48 */
int64_t _fx = _deref(_idx(_forces, _add(_mul(_i, 2), 0)));
/* line: 308, column: 39, length: 48 */
int64_t _fy = _deref(_idx(_forces, _add(_mul(_i, 2), 1)));
/* line: 309, column: 36, length: 21 */
int64_t _ax = _fdiv(_fx, _m);
/* line: 310, column: 8, length: 21 */
int64_t _ay = _fdiv(_fy, _m);
/* line: 313, column: 21, length: 36 */
int64_t _vx_new = _fadd(_vx, _fmul(_ax, _dt));
/* line: 314, column: 17, length: 36 */
int64_t _vy_new = _fadd(_vy, _fmul(_ay, _dt));
/* line: 317, column: 31, length: 38 */
int64_t _x_new = _fadd(_x, _fmul(_vx_new, _dt));
/* line: 318, column: 18, length: 38 */
int64_t _y_new = _fadd(_y, _fmul(_vy_new, _dt));
/* line: 321, column: 41, length: 48 */
_body_set_vx(_bodies, _nbodies, _stride, _i, _vx_new);
/* line: 324, column: 17, length: 48 */
_body_set_vy(_bodies, _nbodies, _stride, _i, _vy_new);
/* line: 325, column: 51, length: 47 */
_body_set_x(_bodies, _nbodies, _stride, _i, _x_new);
/* line: 329, column: 11, length: 47 */
_body_set_y(_bodies, _nbodies, _stride, _i, _y_new);
/* line: 331, column: 6, length: 14 */
_i = _add(_i, 1);
}
/* line: 333, column: 0, length: 9 */
return 0;
return 0;
}
/* line: 349, column: 59, length: 721 */
int64_t _print_bodies(int64_t _bodies, int64_t _nbodies, int64_t _stride) {
/* line: 335, column: 64, length: 10 */
int64_t _i = 0;
/* line: 349, column: 35, length: 634 */
while (_lt(_i, _nbodies)) {
/* line: 336, column: 39, length: 14 */
_puts((int64_t)(int64_t*)(int64_t[]){ 139475578690, 0 });
/* line: 336, column: 56, length: 8 */
_puti(_i);
/* line: 337, column: 18, length: 13 */
_puts((int64_t)(int64_t*)(int64_t[]){ 1031282746, 0 });
/* line: 338, column: 8, length: 49 */
int64_t _x_i = _body_get_x(_bodies, _nbodies, _stride, _i);
/* line: 339, column: 8, length: 10 */
_putf(_x_i);
/* line: 339, column: 31, length: 13 */
_puts((int64_t)(int64_t*)(int64_t[]){ 1031348268, 0 });
/* line: 340, column: 32, length: 49 */
int64_t _y_i = _body_get_y(_bodies, _nbodies, _stride, _i);
/* line: 341, column: 17, length: 10 */
_putf(_y_i);
/* line: 342, column: 7, length: 14 */
_puts((int64_t)(int64_t*)(int64_t[]){ 264014012460, 0 });
/* line: 343, column: 24, length: 51 */
int64_t _vx_i = _body_get_vx(_bodies, _nbodies, _stride, _i);
/* line: 343, column: 44, length: 11 */
_putf(_vx_i);
/* line: 345, column: 16, length: 14 */
_puts((int64_t)(int64_t*)(int64_t[]){ 264030789676, 0 });
/* line: 345, column: 76, length: 51 */
int64_t _vy_i = _body_get_vy(_bodies, _nbodies, _stride, _i);
/* line: 347, column: 4, length: 11 */
_putf(_vy_i);
/* line: 347, column: 27, length: 13 */
_puts((int64_t)(int64_t*)(int64_t[]){ 1030561836, 0 });
/* line: 348, column: 25, length: 50 */
int64_t _m_i = _body_get_m(_bodies, _nbodies, _stride, _i);
/* line: 348, column: 44, length: 10 */
_putf(_m_i);
/* line: 349, column: 1, length: 8 */
_putln();
/* line: 349, column: 24, length: 14 */
_i = _add(_i, 1);
}
/* line: 349, column: 43, length: 8 */
_putln();
/* line: 349, column: 57, length: 9 */
return 0;
return 0;
}
/* line: 392, column: 72, length: 1480 */
int64_t _three_body() {
/* line: 350, column: 46, length: 16 */
int64_t _nbodies = 3;
/* line: 351, column: 8, length: 16 */
int64_t _stride = 5;
/* line: 351, column: 58, length: 38 */
int64_t _total_size = _mul(_nbodies, _stride);
/* line: 354, column: 10, length: 32 */
int64_t _bodies = _malloc(_total_size);
/* line: 355, column: 10, length: 49 */
_body_set_x(_bodies, _nbodies, _stride, 0, _fzero());
/* line: 355, column: 65, length: 49 */
_body_set_y(_bodies, _nbodies, _stride, 0, _fzero());
/* line: 356, column: 54, length: 49 */
_body_set_vx(_bodies, _nbodies, _stride, 0, _fzero());
/* line: 357, column: 46, length: 53 */
_body_set_vy(_bodies, _nbodies, _stride, 0, _to_float(1));
/* line: 358, column: 38, length: 54 */
_body_set_m(_bodies, _nbodies, _stride, 0, _to_float(10));
/* line: 361, column: 18, length: 53 */
_body_set_x(_bodies, _nbodies, _stride, 1, _to_float(5));
/* line: 362, column: 8, length: 49 */
_body_set_y(_bodies, _nbodies, _stride, 1, _fzero());
/* line: 363, column: 2, length: 49 */
_body_set_vx(_bodies, _nbodies, _stride, 1, _fzero());
/* line: 363, column: 67, length: 54 */
_body_set_vy(_bodies, _nbodies, _stride, 1, _to_float(-1));
/* line: 364, column: 59, length: 54 */
_body_set_m(_bodies, _nbodies, _stride, 1, _to_float(10));
/* line: 365, column: 53, length: 49 */
_body_set_x(_bodies, _nbodies, _stride, 2, _fzero());
/* line: 368, column: 26, length: 53 */
_body_set_y(_bodies, _nbodies, _stride, 2, _to_float(7));
/* line: 371, column: 13, length: 54 */
_body_set_vx(_bodies, _nbodies, _stride, 2, _to_float(-1));
/* line: 372, column: 38, length: 49 */
_body_set_vy(_bodies, _nbodies, _stride, 2, _fzero());
/* line: 376, column: 8, length: 53 */
_body_set_m(_bodies, _nbodies, _stride, 2, _to_float(5));
/* line: 377, column: 16, length: 25 */
_puts((int64_t)(int64_t*)(int64_t[]){ 2336349412250971721, 2878957185758291, 0 });
/* line: 378, column: 7, length: 38 */
_print_bodies(_bodies, _nbodies, _stride);
/* line: 381, column: 2, length: 20 */
int64_t _dt = _fpoint01();
/* line: 382, column: 13, length: 17 */
int64_t _steps = 1000;
/* line: 383, column: 5, length: 13 */
int64_t _step = 0;
/* line: 390, column: 32, length: 123 */
while (_lt(_step, _steps)) {
/* line: 387, column: 3, length: 43 */
_update_bodies(_bodies, _nbodies, _stride, _dt);
/* line: 390, column: 15, length: 20 */
_step = _add(_step, 1);
}
/* line: 390, column: 59, length: 27 */
_puts((int64_t)(int64_t*)(int64_t[]){ 8382078981329807686, 7310580662470538337, 8306, 0 });
/* line: 390, column: 76, length: 12 */
_puti(_steps);
/* line: 392, column: 12, length: 18 */
_puts((int64_t)(int64_t*)(int64_t[]){ 737028415604159264, 0 });
/* line: 392, column: 55, length: 38 */
_print_bodies(_bodies, _nbodies, _stride);
/* line: 392, column: 70, length: 9 */
return 0;
return 0;
}
/* line: 396, column: 1, length: 46 */
int64_t _main() {
/* line: 394, column: 17, length: 13 */
_three_body();
/* line: 395, column: 13, length: 9 */
return 0;
return 0;
}

/* BEGIN MAIN */
int main() {
_main();
}