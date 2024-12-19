extern fun put(x);
extern fun putnum(x);
extern fun fprint(x);
extern fun fadd(x, y);
extern fun fsub(x, y);
extern fun fmul(x, y);
extern fun fdiv(x, y);
extern fun fneg(x);
extern fun frem(x, y);
extern fun flt(x, y);
extern fun lt(x, y);
extern fun add(x, y);

extern fun read();
extern fun write(ch);

extern fun malloc(size);
extern fun free(ptr);
extern fun deref(ptr);
extern fun idx(ptr, i);

fun sin(x) {
    x = frem(x, fmul(2.0, 3.14159265358979323846));
    if (flt(x, 0.0)) {
        x = fadd(x, fmul(2, 3.14159265358979323846));
    } else {}

    let result = 0.0;
    let term = x;
    let i = 1.0;
    let sign = 1.0;
    
    while (lt(i, 30.0)) {
        result = fadd(result, fmul(sign, term));
        term = fmul(term, fdiv(fmul(x, x), fmul(fadd(i, 1.0), fadd(i, 2.0))));
        sign = fneg(sign);
        i = fadd(i, 2.0);
    }

    return result;
}

fun newline() {
    put('\n');
}

put('H');
put('e');
put('l');
put('l');
put('o');
put(',');
put(' ');
put('W');
put('o');
put('r');
put('l');
put('d');
put('!');
newline();

put('>');
put(' ');
let x = read();
newline();
put('Y');
put('o');
put('u');
put(' ');
put('e');
put('n');
put('t');
put('e');
put('r');
put('e');
put('d');
put(' ');
put('\'');
put(x);
put('\'');
put('.');
newline();

fprint(sin(0.0));
newline();
fprint(sin(fdiv(3.14159265358979323846, 4.0)));
newline();
fprint(sin(3.14159265358979323846));
newline();