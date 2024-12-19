extern fun fadd(x, y);
extern fun fsub(x, y);
extern fun fmul(x, y);
extern fun fdiv(x, y);
extern fun frem(x, y);
extern fun flt(x, y);

extern fun add(x, y);
extern fun mul(x, y);
extern fun div(x, y);
extern fun lt(x, y);
extern fun eq(x, y);

extern fun put(ch);
extern fun putnum(n);
extern fun fprint(ch);
fun newline() {
    put('\n');
}

extern fun to_float(n);
extern fun to_int(n);
extern fun round(n);
extern fun floor(n);
extern fun ceil(n);

extern fun deref(ptr);

let static MAX_ITER = 100;

fun hsv_to_rgb(h, s, v) {
    let r = h;
    let g = s;
    let b = v;

    h = fdiv(deref(h), 360.0); // Normalize hue to [0, 1]
    s = deref(s);
    v = deref(v);

    let i = to_int(fmul(h, 6.0)); // Calculate the sector index (0-5)
    let f = fsub(fmul(h, 6.0), to_float(i)); // Fractional part
    let w = fmul(fmul(255.0, v), fsub(1.0, s)); // Base value
    let q = fmul(fmul(255.0, v), fsub(1.0, fmul(s, f))); // Interpolated value 1
    let t = fmul(fmul(255.0, v), fsub(1.0, fmul(s, fsub(1.0, f)))); // Interpolated value 2
    v = fmul(255.0, v); // Maximum intensity

    if (eq(i, 0)) {
        *r = v; *g = t; *b = w;
    } else if (eq(i, 1)) {
        *r = q; *g = v; *b = w;
    } else if (eq(i, 2)) {
        *r = w; *g = v; *b = t;
    } else if (eq(i, 3)) {
        *r = w; *g = q; *b = v;
    } else if (eq(i, 4)) {
        *r = t; *g = w; *b = v;
    } else {
        *r = v; *g = w; *b = q;
    }
}

fun print_colored_char(ch, hue, saturation, value) {
    hsv_to_rgb(&hue, &saturation, &value);
    let r = floor(hue);
    let g = floor(saturation);
    let b = floor(value);

    put(27);
    put('[');
    put('3');
    put('8');
    put(';');
    put('2');
    put(';');
    putnum(to_int(r));
    put(';');
    putnum(to_int(g));
    put(';');
    putnum(to_int(b));
    put('m');
    put(ch);
}

fun print_mandelbrot_iter(iter) {
    let range = 360.0;
    let offset = 90.0;

    iter = mul(iter, 5);

    let hue = fadd(fmul(fdiv(to_float(iter), to_float(MAX_ITER)), range), offset); // Map iterations to 0-270
    let saturation = 1.0;
    let value = 1.0;

    let ch = if (lt(iter, div(mul(MAX_ITER, 1), 6))) {
        '.'
    } else if (lt(iter, div(mul(MAX_ITER, 2), 6))) {
        ','
    } else if (lt(iter, div(mul(MAX_ITER, 3), 6))) {
        '+'
    } else if (lt(iter, div(mul(MAX_ITER, 4), 6))) {
        '*'
    } else if (lt(iter, div(mul(MAX_ITER, 5), 6))) {
        '#'
    } else {
        '@'
    };

    print_colored_char(ch, hue, saturation, value);
}

fun mandelbrot(real, imag) {
    let max_iter = MAX_ITER;
    let zr = 0.0;
    let zi = 0.0;
    let iter = 0;

    while (lt(iter, max_iter)) {
        let zr2 = fmul(zr, zr);
        let zi2 = fmul(zi, zi);
        let magnitude2 = fadd(zr2, zi2);

        if (flt(magnitude2, 4.0)) {
            let temp = zr;
            zr = fadd(fsub(zr2, zi2), real);
            zi = fadd(fmul(2.0, fmul(temp, zi)), imag);
            iter = add(iter, 1);
        } else {
            break;
        }
    }
    return iter;
}

fun render(min_real, max_real, min_imag, max_imag) {
    let width = 80;
    let height = 24;
    // let width = 3200;
    // let height = 720;

    let dr = fdiv(fsub(max_real, min_real), fsub(to_float(width), 1.0));
    let di = fdiv(fsub(max_imag, min_imag), fsub(to_float(height), 1.0));

    let y = 0;
    while (lt(y, height)) {
        let imag = fadd(min_imag, fmul(to_float(y), di));
        let x = 0;

        while (lt(x, width)) {
            let real = fadd(min_real, fmul(to_float(x), dr));
            let iter = mandelbrot(real, imag);
            print_mandelbrot_iter(iter);
            x = add(x, 1);
        }

        newline();
        y = add(y, 1);
    }
}

fun zoom_render(x_center, y_center, zoom) {
    let x_min = fsub(x_center, fdiv(1.0, zoom));
    let x_max = fadd(x_center, fdiv(1.0, zoom));
    let y_min = fsub(y_center, fdiv(1.0, zoom));
    let y_max = fadd(y_center, fdiv(1.0, zoom));

    render(x_min, x_max, y_min, y_max);
}



// Example render call with zoomed-in region
render(-2.0, 1.0, -1.0, 1.0); // Full view
newline();

// Seahorse Valley
render(-0.75, -0.74, 0.1, 0.11);
newline();

// Elephant Valley
render(0.28, 0.29, 0.0, 0.02);
newline();

// Triple Spiral Valley
zoom_render(-0.1011, 0.8383, 100.0);
newline();

// The Needle
zoom_render(0.001643721971153, -0.822467633298876, 1000.0);

// Satellites
zoom_render(-1.75, 0.0, 100.0);

// Tail of Seahorse
zoom_render(-0.745428, 0.113009, 300.0);

// Double Spiral Valley
zoom_render(-0.122561, 0.744861, 500.0);

// Box Canyon
zoom_render(-0.743643135, 0.131825963, 10000.0);

// Head Spiral
zoom_render(-0.7463, 0.1102, 200.0);