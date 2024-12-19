#include <stdint.h>
int64_t mage_as_int(double x) {{ return *(int64_t*)&x; }}

#if __has_include("ffi.h")
#include "ffi.h"
#endif

/* BEGIN PROCEDURES *//* line: 26, column: 2, length: 23 */
int64_t _fadd(int64_t x, int64_t y);
/* line: 28, column: 1, length: 23 */
int64_t _fsub(int64_t x, int64_t y);
/* line: 28, column: 24, length: 23 */
int64_t _fmul(int64_t x, int64_t y);
/* line: 30, column: 19, length: 23 */
int64_t _fdiv(int64_t x, int64_t y);
/* line: 32, column: 1, length: 23 */
int64_t _frem(int64_t x, int64_t y);
/* line: 33, column: 9, length: 23 */
int64_t _flt(int64_t x, int64_t y);
/* line: 35, column: 15, length: 22 */
int64_t _add(int64_t x, int64_t y);
/* line: 35, column: 37, length: 22 */
int64_t _mul(int64_t x, int64_t y);
/* line: 36, column: 1, length: 22 */
int64_t _div(int64_t x, int64_t y);
/* line: 37, column: 4, length: 21 */
int64_t _lt(int64_t x, int64_t y);
/* line: 39, column: 7, length: 22 */
int64_t _eq(int64_t x, int64_t y);
/* line: 39, column: 27, length: 20 */
int64_t _put(int64_t ch);
/* line: 39, column: 49, length: 22 */
int64_t _putnum(int64_t n);
/* line: 40, column: 2, length: 23 */
int64_t _fprint(int64_t ch);
/* line: 40, column: 34, length: 32 */
int64_t _newline() {
/* line: 40, column: 32, length: 10 */
_put('\n');
}
/* line: 40, column: 60, length: 24 */
int64_t _to_float(int64_t n);
/* line: 41, column: 18, length: 22 */
int64_t _to_int(int64_t n);
/* line: 41, column: 39, length: 21 */
int64_t _round(int64_t n);
/* line: 41, column: 60, length: 21 */
int64_t _floor(int64_t n);
/* line: 42, column: 19, length: 21 */
int64_t _ceil(int64_t n);
/* line: 42, column: 43, length: 24 */
int64_t _deref(int64_t ptr);
/* line: 42, column: 69, length: 26 */
static int64_t _MAX_ITER = 100;
/* line: 73, column: 13, length: 764 */
int64_t _hsv_to_rgb(int64_t _h, int64_t _s, int64_t _v) {
/* line: 43, column: 30, length: 10 */
int64_t _r = _h;
/* line: 43, column: 45, length: 10 */
int64_t _g = _s;
/* line: 43, column: 60, length: 10 */
int64_t _b = _v;
/* line: 44, column: 0, length: 26 */
_h = _fdiv(_deref(_h), mage_as_int(360.0));
/* line: 44, column: 19, length: 13 */
_s = _deref(_s);
/* line: 44, column: 37, length: 13 */
_v = _deref(_v);
/* line: 47, column: 6, length: 29 */
int64_t _i = _to_int(_fmul(_h, mage_as_int(6.0)));
/* line: 48, column: 20, length: 40 */
int64_t _f = _fsub(_fmul(_h, mage_as_int(6.0)), _to_float(_i));
/* line: 50, column: 10, length: 43 */
int64_t _w = _fmul(_fmul(mage_as_int(255.0), _v), _fsub(mage_as_int(1.0), _s));
/* line: 52, column: 9, length: 52 */
int64_t _q = _fmul(_fmul(mage_as_int(255.0), _v), _fsub(mage_as_int(1.0), _fmul(_s, _f)));
/* line: 54, column: 19, length: 63 */
int64_t _t = _fmul(_fmul(mage_as_int(255.0), _v), _fsub(mage_as_int(1.0), _fmul(_s, _fsub(mage_as_int(1.0), _f))));
/* line: 55, column: 17, length: 19 */
_v = _fmul(mage_as_int(255.0), _v);
/* line: 73, column: 12, length: 335 */
if (_eq(_i, 0)) {
/* line: 57, column: 10, length: 7 */
*(int64_t*)_r = _v;
/* line: 57, column: 18, length: 7 */
*(int64_t*)_g = _t;
/* line: 57, column: 26, length: 7 */
*(int64_t*)_b = _w;
} else {
if (_eq(_i, 1)) {
/* line: 61, column: 28, length: 7 */
*(int64_t*)_r = _q;
/* line: 61, column: 36, length: 7 */
*(int64_t*)_g = _v;
/* line: 61, column: 44, length: 7 */
*(int64_t*)_b = _w;
} else {
if (_eq(_i, 2)) {
/* line: 62, column: 34, length: 7 */
*(int64_t*)_r = _w;
/* line: 62, column: 42, length: 7 */
*(int64_t*)_g = _v;
/* line: 63, column: 7, length: 7 */
*(int64_t*)_b = _t;
} else {
if (_eq(_i, 3)) {
/* line: 64, column: 26, length: 7 */
*(int64_t*)_r = _w;
/* line: 65, column: 3, length: 7 */
*(int64_t*)_g = _q;
/* line: 65, column: 11, length: 7 */
*(int64_t*)_b = _v;
} else {
if (_eq(_i, 4)) {
/* line: 69, column: 0, length: 7 */
*(int64_t*)_r = _t;
/* line: 69, column: 8, length: 7 */
*(int64_t*)_g = _w;
/* line: 70, column: 2, length: 7 */
*(int64_t*)_b = _v;
} else {
/* line: 72, column: 3, length: 7 */
*(int64_t*)_r = _v;
/* line: 72, column: 11, length: 7 */
*(int64_t*)_g = _w;
/* line: 73, column: 5, length: 7 */
*(int64_t*)_b = _q;
}
}
}
}
}
}
/* line: 93, column: 9, length: 400 */
int64_t _print_colored_char(int64_t _ch, int64_t _hue, int64_t _saturation, int64_t _value) {
/* line: 78, column: 22, length: 38 */
_hsv_to_rgb(((int64_t)&_hue), ((int64_t)&_saturation), ((int64_t)&_value));
/* line: 80, column: 9, length: 19 */
int64_t _r = _floor(_hue);
/* line: 83, column: 24, length: 26 */
int64_t _g = _floor(_saturation);
/* line: 84, column: 16, length: 21 */
int64_t _b = _floor(_value);
/* line: 85, column: 7, length: 8 */
_put(27);
/* line: 85, column: 21, length: 9 */
_put('[');
/* line: 87, column: 11, length: 9 */
_put('3');
/* line: 88, column: 0, length: 9 */
_put('8');
/* line: 89, column: 13, length: 9 */
_put(';');
/* line: 89, column: 27, length: 9 */
_put('2');
/* line: 89, column: 41, length: 9 */
_put(';');
/* line: 89, column: 64, length: 18 */
_putnum(_to_int(_r));
/* line: 89, column: 78, length: 9 */
_put(';');
/* line: 89, column: 101, length: 18 */
_putnum(_to_int(_g));
/* line: 90, column: 5, length: 9 */
_put(';');
/* line: 91, column: 2, length: 18 */
_putnum(_to_int(_b));
/* line: 91, column: 16, length: 9 */
_put('m');
/* line: 93, column: 7, length: 8 */
_put(_ch);
}
/* line: 119, column: 38, length: 652 */
int64_t _print_mandelbrot_iter(int64_t _iter) {
/* line: 95, column: 0, length: 18 */
int64_t _range = mage_as_int(360.0);
/* line: 95, column: 23, length: 18 */
int64_t _offset = mage_as_int(90.0);
/* line: 95, column: 49, length: 20 */
_iter = _mul(_iter, 5);
/* line: 99, column: 3, length: 78 */
int64_t _hue = _fadd(_fmul(_fdiv(_to_float(_iter), _to_float(_MAX_ITER)), _range), _offset);
/* line: 99, column: 30, length: 21 */
int64_t _saturation = mage_as_int(1.0);
/* line: 99, column: 51, length: 16 */
int64_t _value = mage_as_int(1.0);
/* line: 118, column: 15, length: 354 */
int64_t _ch = _lt(_iter, _div(_mul(_MAX_ITER, 1), 6))? '.' : _lt(_iter, _div(_mul(_MAX_ITER, 2), 6))? ',' : _lt(_iter, _div(_mul(_MAX_ITER, 3), 6))? '+' : _lt(_iter, _div(_mul(_MAX_ITER, 4), 6))? '*' : _lt(_iter, _div(_mul(_MAX_ITER, 5), 6))? '#' : '@';
/* line: 119, column: 36, length: 47 */
_print_colored_char(_ch, _hue, _saturation, _value);
}
/* line: 140, column: 30, length: 519 */
int64_t _mandelbrot(int64_t _real, int64_t _imag) {
/* line: 122, column: 19, length: 24 */
int64_t _max_iter = _MAX_ITER;
/* line: 123, column: 10, length: 13 */
int64_t _zr = mage_as_int(0.0);
/* line: 123, column: 28, length: 13 */
int64_t _zi = mage_as_int(0.0);
/* line: 124, column: 1, length: 13 */
int64_t _iter = 0;
/* line: 140, column: 16, length: 388 */
while (_lt(_iter, _max_iter)) {
/* line: 125, column: 11, length: 23 */
int64_t _zr2 = _fmul(_zr, _zr);
/* line: 126, column: 10, length: 23 */
int64_t _zi2 = _fmul(_zi, _zi);
/* line: 129, column: 5, length: 32 */
int64_t _magnitude2 = _fadd(_zr2, _zi2);
/* line: 140, column: 10, length: 239 */
if (_flt(_magnitude2, mage_as_int(4.0))) {
/* line: 133, column: 43, length: 14 */
int64_t _temp = _zr;
/* line: 135, column: 15, length: 32 */
_zr = _fadd(_fsub(_zr2, _zi2), _real);
/* line: 138, column: 0, length: 43 */
_zi = _fadd(_fmul(mage_as_int(2.0), _fmul(_temp, _zi)), _imag);
/* line: 139, column: 32, length: 20 */
_iter = _add(_iter, 1);
} else {
/* line: 139, column: 68, length: 6 */
break;
}
}
/* line: 140, column: 28, length: 12 */
return _iter;
}
/* line: 163, column: 17, length: 642 */
int64_t _render(int64_t _min_real, int64_t _max_real, int64_t _min_imag, int64_t _max_imag) {
/* line: 143, column: 14, length: 15 */
int64_t _width = 80;
/* line: 144, column: 7, length: 16 */
int64_t _height = 24;
/* line: 147, column: 13, length: 68 */
int64_t _dr = _fdiv(_fsub(_max_real, _min_real), _fsub(_to_float(_width), mage_as_int(1.0)));
/* line: 148, column: 56, length: 69 */
int64_t _di = _fdiv(_fsub(_max_imag, _min_imag), _fsub(_to_float(_height), mage_as_int(1.0)));
/* line: 149, column: 10, length: 10 */
int64_t _y = 0;
/* line: 163, column: 16, length: 369 */
while (_lt(_y, _height)) {
/* line: 151, column: 8, length: 49 */
int64_t _imag = _fadd(_min_imag, _fmul(_to_float(_y), _di));
/* line: 152, column: 0, length: 10 */
int64_t _x = 0;
/* line: 162, column: 25, length: 219 */
while (_lt(_x, _width)) {
/* line: 159, column: 32, length: 49 */
int64_t _real = _fadd(_min_real, _fmul(_to_float(_x), _dr));
/* line: 160, column: 35, length: 34 */
int64_t _iter = _mandelbrot(_real, _imag);
/* line: 161, column: 27, length: 28 */
_print_mandelbrot_iter(_iter);
/* line: 162, column: 5, length: 14 */
_x = _add(_x, 1);
}
/* line: 162, column: 35, length: 10 */
_newline();
/* line: 163, column: 9, length: 14 */
_y = _add(_y, 1);
}
}
/* line: 179, column: 23, length: 282 */
int64_t _zoom_render(int64_t _x_center, int64_t _y_center, int64_t _zoom) {
/* line: 170, column: 16, length: 44 */
int64_t _x_min = _fsub(_x_center, _fdiv(mage_as_int(1.0), _zoom));
/* line: 171, column: 20, length: 44 */
int64_t _x_max = _fadd(_x_center, _fdiv(mage_as_int(1.0), _zoom));
/* line: 174, column: 14, length: 44 */
int64_t _y_min = _fsub(_y_center, _fdiv(mage_as_int(1.0), _zoom));
/* line: 177, column: 0, length: 44 */
int64_t _y_max = _fadd(_y_center, _fdiv(mage_as_int(1.0), _zoom));
/* line: 179, column: 21, length: 35 */
_render(_x_min, _x_max, _y_min, _y_max);
}

/* BEGIN MAIN */
int main() {
_render(mage_as_int(-2.0), mage_as_int(1.0), mage_as_int(-1.0), mage_as_int(1.0));
_newline();
_render(mage_as_int(-0.75), mage_as_int(-0.74), mage_as_int(0.1), mage_as_int(0.11));
_newline();
_render(mage_as_int(0.28), mage_as_int(0.29), mage_as_int(0.0), mage_as_int(0.02));
_newline();
_zoom_render(mage_as_int(-0.1011), mage_as_int(0.8383), mage_as_int(100.0));
_newline();
_zoom_render(mage_as_int(0.001643721971153), mage_as_int(-0.822467633298876), mage_as_int(1000.0));
_zoom_render(mage_as_int(-1.75), mage_as_int(0.0), mage_as_int(100.0));
_zoom_render(mage_as_int(-0.745428), mage_as_int(0.113009), mage_as_int(300.0));
_zoom_render(mage_as_int(-0.122561), mage_as_int(0.744861), mage_as_int(500.0));
_zoom_render(mage_as_int(-0.743643135), mage_as_int(0.131825963), mage_as_int(10000.0));
_zoom_render(mage_as_int(-0.7463), mage_as_int(0.1102), mage_as_int(200.0));
}