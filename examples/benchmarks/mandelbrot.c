#include <stdint.h>
#include <stddef.h>
#include <string.h>
int64_t mage_as_int(double x) {{ return *(int64_t*)&x; }}

#if __has_include("ffi.h")
#include "ffi.h"
#endif

/* BEGIN PROCEDURES *//* line: 38, column: 0, length: 23 */
int64_t _fadd(int64_t x, int64_t y);
/* line: 39, column: 8, length: 23 */
int64_t _fsub(int64_t x, int64_t y);
/* line: 41, column: 15, length: 23 */
int64_t _fmul(int64_t x, int64_t y);
/* line: 41, column: 38, length: 23 */
int64_t _fdiv(int64_t x, int64_t y);
/* line: 42, column: 3, length: 23 */
int64_t _frem(int64_t x, int64_t y);
/* line: 43, column: 8, length: 23 */
int64_t _flt(int64_t x, int64_t y);
/* line: 45, column: 11, length: 22 */
int64_t _add(int64_t x, int64_t y);
/* line: 45, column: 33, length: 22 */
int64_t _mul(int64_t x, int64_t y);
/* line: 45, column: 55, length: 22 */
int64_t _div(int64_t x, int64_t y);
/* line: 46, column: 6, length: 21 */
int64_t _lt(int64_t x, int64_t y);
/* line: 46, column: 28, length: 22 */
int64_t _eq(int64_t x, int64_t y);
/* line: 46, column: 48, length: 20 */
int64_t _puts(int64_t s);
/* line: 47, column: 7, length: 23 */
int64_t _putsln(int64_t s);
/* line: 47, column: 27, length: 20 */
int64_t _put(int64_t ch);
/* line: 47, column: 49, length: 22 */
int64_t _putnum(int64_t n);
/* line: 48, column: 10, length: 23 */
int64_t _fprint(int64_t ch);
/* line: 48, column: 56, length: 46 */
int64_t _newline() {
/* line: 48, column: 40, length: 10 */
_put('\n');
/* line: 48, column: 54, length: 9 */
return 0;
return 0;
}
/* line: 49, column: 1, length: 24 */
int64_t _to_float(int64_t n);
/* line: 49, column: 23, length: 22 */
int64_t _to_int(int64_t n);
/* line: 49, column: 44, length: 21 */
int64_t _round(int64_t n);
/* line: 49, column: 65, length: 21 */
int64_t _floor(int64_t n);
/* line: 49, column: 86, length: 21 */
int64_t _ceil(int64_t n);
/* line: 50, column: 18, length: 24 */
int64_t _deref(int64_t ptr);
/* line: 51, column: 0, length: 27 */
static int64_t _MAX_ITER = 1000;
/* line: 53, column: 4, length: 24 */
static int64_t _WIDTH = 1600;
/* line: 53, column: 29, length: 24 */
static int64_t _HEIGHT = 900;
/* line: 91, column: 14, length: 764 */
int64_t _hsv_to_rgb(int64_t _h, int64_t _s, int64_t _v) {
/* line: 55, column: 12, length: 10 */
int64_t _r = _h;
/* line: 55, column: 27, length: 10 */
int64_t _g = _s;
/* line: 56, column: 10, length: 10 */
int64_t _b = _v;
/* line: 57, column: 15, length: 26 */
_h = _fdiv(_deref(_h), mage_as_int(360.0));
/* line: 58, column: 2, length: 13 */
_s = _deref(_s);
/* line: 58, column: 20, length: 13 */
_v = _deref(_v);
/* line: 59, column: 28, length: 29 */
int64_t _i = _to_int(_fmul(_h, mage_as_int(6.0)));
/* line: 61, column: 15, length: 40 */
int64_t _f = _fsub(_fmul(_h, mage_as_int(6.0)), _to_float(_i));
/* line: 63, column: 19, length: 43 */
int64_t _w = _fmul(_fmul(mage_as_int(255.0), _v), _fsub(mage_as_int(1.0), _s));
/* line: 67, column: 36, length: 52 */
int64_t _q = _fmul(_fmul(mage_as_int(255.0), _v), _fsub(mage_as_int(1.0), _fmul(_s, _f)));
/* line: 69, column: 9, length: 63 */
int64_t _t = _fmul(_fmul(mage_as_int(255.0), _v), _fsub(mage_as_int(1.0), _fmul(_s, _fsub(mage_as_int(1.0), _f))));
/* line: 70, column: 10, length: 19 */
_v = _fmul(mage_as_int(255.0), _v);
/* line: 91, column: 13, length: 335 */
if (_eq(_i, 0)) {
/* line: 71, column: 17, length: 7 */
*(int64_t*)_r = _v;
/* line: 71, column: 25, length: 7 */
*(int64_t*)_g = _t;
/* line: 73, column: 6, length: 7 */
*(int64_t*)_b = _w;
} else {
if (_eq(_i, 1)) {
/* line: 76, column: 8, length: 7 */
*(int64_t*)_r = _q;
/* line: 77, column: 2, length: 7 */
*(int64_t*)_g = _v;
/* line: 77, column: 10, length: 7 */
*(int64_t*)_b = _w;
} else {
if (_eq(_i, 2)) {
/* line: 80, column: 11, length: 7 */
*(int64_t*)_r = _w;
/* line: 80, column: 19, length: 7 */
*(int64_t*)_g = _v;
/* line: 81, column: 4, length: 7 */
*(int64_t*)_b = _t;
} else {
if (_eq(_i, 3)) {
/* line: 83, column: 10, length: 7 */
*(int64_t*)_r = _w;
/* line: 84, column: 4, length: 7 */
*(int64_t*)_g = _q;
/* line: 84, column: 12, length: 7 */
*(int64_t*)_b = _v;
} else {
if (_eq(_i, 4)) {
/* line: 89, column: 2, length: 7 */
*(int64_t*)_r = _t;
/* line: 89, column: 10, length: 7 */
*(int64_t*)_g = _w;
/* line: 89, column: 18, length: 7 */
*(int64_t*)_b = _v;
} else {
/* line: 90, column: 13, length: 7 */
*(int64_t*)_r = _v;
/* line: 90, column: 21, length: 7 */
*(int64_t*)_g = _w;
/* line: 91, column: 6, length: 7 */
*(int64_t*)_b = _q;
}
}
}
}
}
return 0;
}
/* line: 105, column: 11, length: 400 */
int64_t _print_colored_char(int64_t _ch, int64_t _hue, int64_t _saturation, int64_t _value) {
/* line: 95, column: 61, length: 38 */
_hsv_to_rgb(((int64_t)&_hue), ((int64_t)&_saturation), ((int64_t)&_value));
/* line: 95, column: 85, length: 19 */
int64_t _r = _floor(_hue);
/* line: 96, column: 6, length: 26 */
int64_t _g = _floor(_saturation);
/* line: 97, column: 6, length: 21 */
int64_t _b = _floor(_value);
/* line: 97, column: 20, length: 8 */
_put(27);
/* line: 99, column: 12, length: 9 */
_put('[');
/* line: 99, column: 26, length: 9 */
_put('3');
/* line: 99, column: 40, length: 9 */
_put('8');
/* line: 99, column: 54, length: 9 */
_put(';');
/* line: 101, column: 1, length: 9 */
_put('2');
/* line: 101, column: 15, length: 9 */
_put(';');
/* line: 101, column: 38, length: 18 */
_putnum(_to_int(_r));
/* line: 101, column: 52, length: 9 */
_put(';');
/* line: 103, column: 10, length: 18 */
_putnum(_to_int(_g));
/* line: 103, column: 24, length: 9 */
_put(';');
/* line: 103, column: 47, length: 18 */
_putnum(_to_int(_b));
/* line: 104, column: 8, length: 9 */
_put('m');
/* line: 105, column: 9, length: 8 */
_put(_ch);
return 0;
}
/* line: 131, column: 31, length: 652 */
int64_t _print_mandelbrot_iter(int64_t _iter) {
/* line: 107, column: 4, length: 18 */
int64_t _range = mage_as_int(360.0);
/* line: 107, column: 27, length: 18 */
int64_t _offset = mage_as_int(90.0);
/* line: 108, column: 0, length: 20 */
_iter = _mul(_iter, 5);
/* line: 113, column: 39, length: 78 */
int64_t _hue = _fadd(_fmul(_fdiv(_to_float(_iter), _to_float(_MAX_ITER)), _range), _offset);
/* line: 116, column: 11, length: 21 */
int64_t _saturation = mage_as_int(1.0);
/* line: 117, column: 3, length: 16 */
int64_t _value = mage_as_int(1.0);
/* line: 130, column: 32, length: 354 */
int64_t _ch = _lt(_iter, _div(_mul(_MAX_ITER, 1), 6))? '.' : _lt(_iter, _div(_mul(_MAX_ITER, 2), 6))? ',' : _lt(_iter, _div(_mul(_MAX_ITER, 3), 6))? '+' : _lt(_iter, _div(_mul(_MAX_ITER, 4), 6))? '*' : _lt(_iter, _div(_mul(_MAX_ITER, 5), 6))? '#' : '@';
/* line: 131, column: 29, length: 47 */
_print_colored_char(_ch, _hue, _saturation, _value);
return 0;
}
/* line: 153, column: 12, length: 519 */
int64_t _mandelbrot(int64_t _real, int64_t _imag) {
/* line: 136, column: 5, length: 24 */
int64_t _max_iter = _MAX_ITER;
/* line: 139, column: 3, length: 13 */
int64_t _zr = mage_as_int(0.0);
/* line: 139, column: 21, length: 13 */
int64_t _zi = mage_as_int(0.0);
/* line: 139, column: 39, length: 13 */
int64_t _iter = 0;
/* line: 151, column: 18, length: 388 */
while (_lt(_iter, _max_iter)) {
/* line: 141, column: 15, length: 23 */
int64_t _zr2 = _fmul(_zr, _zr);
/* line: 142, column: 22, length: 23 */
int64_t _zi2 = _fmul(_zi, _zi);
/* line: 145, column: 12, length: 32 */
int64_t _magnitude2 = _fadd(_zr2, _zi2);
/* line: 151, column: 12, length: 239 */
if (_flt(_magnitude2, mage_as_int(4.0))) {
/* line: 146, column: 3, length: 14 */
int64_t _temp = _zr;
/* line: 146, column: 48, length: 32 */
_zr = _fadd(_fsub(_zr2, _zi2), _real);
/* line: 149, column: 14, length: 43 */
_zi = _fadd(_fmul(mage_as_int(2.0), _fmul(_temp, _zi)), _imag);
/* line: 150, column: 19, length: 20 */
_iter = _add(_iter, 1);
} else {
/* line: 150, column: 55, length: 6 */
break;
}
}
/* line: 153, column: 10, length: 12 */
return _iter;
return 0;
}
/* line: 180, column: 48, length: 750 */
int64_t _render(int64_t _min_real, int64_t _max_real, int64_t _min_imag, int64_t _max_imag, int64_t _should_print) {
/* line: 155, column: 10, length: 18 */
int64_t _width = _WIDTH;
/* line: 155, column: 35, length: 20 */
int64_t _height = _HEIGHT;
/* line: 157, column: 42, length: 68 */
int64_t _dr = _fdiv(_fsub(_max_real, _min_real), _fsub(_to_float(_width), mage_as_int(1.0)));
/* line: 161, column: 20, length: 69 */
int64_t _di = _fdiv(_fsub(_max_imag, _min_imag), _fsub(_to_float(_height), mage_as_int(1.0)));
/* line: 162, column: 10, length: 10 */
int64_t _y = 0;
/* line: 180, column: 47, length: 456 */
while (_lt(_y, _height)) {
/* line: 168, column: 31, length: 49 */
int64_t _imag = _fadd(_min_imag, _fmul(_to_float(_y), _di));
/* line: 168, column: 50, length: 10 */
int64_t _x = 0;
/* line: 179, column: 12, length: 266 */
while (_lt(_x, _width)) {
/* line: 170, column: 37, length: 49 */
int64_t _real = _fadd(_min_real, _fmul(_to_float(_x), _dr));
/* line: 171, column: 35, length: 34 */
int64_t _iter = _mandelbrot(_real, _imag);
/* line: 174, column: 38, length: 89 */
if (_should_print) {
/* line: 174, column: 11, length: 28 */
_print_mandelbrot_iter(_iter);
} else {

}
/* line: 174, column: 52, length: 14 */
_x = _add(_x, 1);
}
/* line: 180, column: 26, length: 59 */
if (_should_print) {
/* line: 180, column: 7, length: 10 */
_newline();
} else {

}
/* line: 180, column: 40, length: 14 */
_y = _add(_y, 1);
}
return 0;
}
/* line: 186, column: 28, length: 310 */
int64_t _zoom_render(int64_t _x_center, int64_t _y_center, int64_t _zoom, int64_t _should_print) {
/* line: 182, column: 38, length: 44 */
int64_t _x_min = _fsub(_x_center, _fdiv(mage_as_int(1.0), _zoom));
/* line: 183, column: 17, length: 44 */
int64_t _x_max = _fadd(_x_center, _fdiv(mage_as_int(1.0), _zoom));
/* line: 184, column: 24, length: 44 */
int64_t _y_min = _fsub(_y_center, _fdiv(mage_as_int(1.0), _zoom));
/* line: 185, column: 22, length: 44 */
int64_t _y_max = _fadd(_y_center, _fdiv(mage_as_int(1.0), _zoom));
/* line: 186, column: 26, length: 49 */
_render(_x_min, _x_max, _y_min, _y_max, _should_print);
return 0;
}

/* BEGIN MAIN */
int main() {
_zoom_render(mage_as_int(-0.743643887037151), mage_as_int(0.13182590420533), mage_as_int(100.0), 0);
_putsln((int64_t)(int64_t*)(int64_t[]){ 7954889800286105412, 9402398144619876, 0 });
}