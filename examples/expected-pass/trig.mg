extern fun read();
extern fun write(x);

extern fun putc(x);
extern fun puti(x);
extern fun putf(x);
extern fun fadd(x, y);
extern fun fsub(x, y);
extern fun fmul(x, y);
extern fun fdiv(x, y);
extern fun fneg(x);
extern fun frem(x, y);
extern fun flt(x, y);
extern fun lt(x, y);
extern fun add(x, y);

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
    putc('\n');
}

putc('H');
putc('e');
putc('l');
putc('l');
putc('o');
putc(',');
putc(' ');
putc('W');
putc('o');
putc('r');
putc('l');
putc('d');
putc('!');
newline();

putc('>');
putc(' ');
let x = read();
newline();
putc('Y');
putc('o');
putc('u');
putc(' ');
putc('e');
putc('n');
putc('t');
putc('e');
putc('r');
putc('e');
putc('d');
putc(' ');
putc('\'');
putc(x);
putc('\'');
putc('.');
newline();

putf(sin(0.0));
newline();
putf(sin(fdiv(3.14159265358979323846, 4.0)));
newline();
putf(sin(3.14159265358979323846));
newline();