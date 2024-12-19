#include <stdint.h>
int64_t mage_as_int(double x) {{ return *(int64_t*)&x; }}

#if __has_include("ffi.h")
#include "ffi.h"
#endif

/* BEGIN PROCEDURES *//* line: 1, column: 0, length: 19 */
int64_t _put(int64_t x);
/* line: 2, column: 0, length: 22 */
int64_t _putnum(int64_t x);
/* line: 3, column: 0, length: 22 */
int64_t _fprint(int64_t x);
/* line: 4, column: 0, length: 23 */
int64_t _fadd(int64_t x, int64_t y);
/* line: 5, column: 0, length: 23 */
int64_t _fsub(int64_t x, int64_t y);
/* line: 6, column: 0, length: 23 */
int64_t _fmul(int64_t x, int64_t y);
/* line: 7, column: 0, length: 23 */
int64_t _fdiv(int64_t x, int64_t y);
/* line: 8, column: 0, length: 20 */
int64_t _fneg(int64_t x);
/* line: 9, column: 0, length: 23 */
int64_t _frem(int64_t x, int64_t y);
/* line: 10, column: 0, length: 22 */
int64_t _flt(int64_t x, int64_t y);
/* line: 11, column: 0, length: 21 */
int64_t _lt(int64_t x, int64_t y);
/* line: 13, column: 0, length: 23 */
int64_t _add(int64_t x, int64_t y);
/* line: 14, column: 0, length: 19 */
int64_t _read();
/* line: 16, column: 0, length: 23 */
int64_t _write(int64_t ch);
/* line: 17, column: 0, length: 25 */
int64_t _malloc(int64_t size);
/* line: 18, column: 0, length: 22 */
int64_t _free(int64_t ptr);
/* line: 19, column: 0, length: 23 */
int64_t _deref(int64_t ptr);
/* line: 21, column: 0, length: 25 */
int64_t _idx(int64_t ptr, int64_t i);
/* line: 40, column: 1, length: 473 */
int64_t _sin(int64_t _x) {
/* line: 22, column: 51, length: 47 */
_x = _frem(_x, _fmul(mage_as_int(2.0), mage_as_int(3.141592653589793)));
/* line: 27, column: 4, length: 92 */
if (_flt(_x, mage_as_int(0.0))) {
/* line: 24, column: 53, length: 45 */
_x = _fadd(_x, _fmul(2, mage_as_int(3.141592653589793)));
} else {

}
/* line: 27, column: 21, length: 17 */
int64_t _result = mage_as_int(0.0);
/* line: 28, column: 17, length: 13 */
int64_t _term = _x;
/* line: 29, column: 16, length: 12 */
int64_t _i = mage_as_int(1.0);
/* line: 30, column: 19, length: 15 */
int64_t _sign = mage_as_int(1.0);
/* line: 39, column: 4, length: 214 */
while (_lt(_i, mage_as_int(30.0))) {
/* line: 33, column: 48, length: 40 */
_result = _fadd(_result, _fmul(_sign, _term));
/* line: 34, column: 78, length: 70 */
_term = _fmul(_term, _fdiv(_fmul(_x, _x), _fmul(_fadd(_i, mage_as_int(1.0)), _fadd(_i, mage_as_int(2.0)))));
/* line: 35, column: 26, length: 18 */
_sign = _fneg(_sign);
/* line: 36, column: 25, length: 17 */
_i = _fadd(_i, mage_as_int(2.0));
}
/* line: 39, column: 18, length: 14 */
return _result;
}
/* line: 44, column: 1, length: 32 */
int64_t _newline() {
/* line: 43, column: 14, length: 10 */
_put('\n');
}

/* BEGIN MAIN */
int main() {
_put('H');
_put('e');
_put('l');
_put('l');
_put('o');
_put(',');
_put(' ');
_put('W');
_put('o');
_put('r');
_put('l');
_put('d');
_put('!');
_newline();
_put('>');
_put(' ');
int64_t _x = _read();
_newline();
_put('Y');
_put('o');
_put('u');
_put(' ');
_put('e');
_put('n');
_put('t');
_put('e');
_put('r');
_put('e');
_put('d');
_put(' ');
_put('\'');
_put(_x);
_put('\'');
_put('.');
_newline();
_fprint(_sin(mage_as_int(0.0)));
_newline();
_fprint(_sin(_fdiv(mage_as_int(3.141592653589793), mage_as_int(4.0))));
_newline();
_fprint(_sin(mage_as_int(3.141592653589793)));
_newline();
}