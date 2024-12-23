// =====================================
// Three-body problem in Mage (float-safe)
// =====================================

// We assume these external functions exist:

// -- Memory/Pointer
extern fun malloc(size);
extern fun idx(ptr, off);
extern fun deref(ptr);

// -- Printing
extern fun puts(s);
extern fun puti(n);     // prints an int
extern fun putf(f);     // prints a float
extern fun putc(ch);


// -- Integer arithmetic
extern fun add(x, y);   // int
extern fun sub(x, y);   // int
extern fun mul(x, y);   // int
extern fun div(x, y);   // int

extern fun eq(x, y);    // int equality -> returns 1 or 0
extern fun lt(x, y);    // int less-than -> returns 1 or 0

// -- Floating-point arithmetic
extern fun fadd(a, b);  // float
extern fun fsub(a, b);  // float
extern fun fmul(a, b);  // float
extern fun fdiv(a, b);  // float

extern fun feq(a, b);   // float equality -> returns 1 or 0
extern fun flt(a, b);   // float less-than -> returns 1 or 0

// -- Conversions
extern fun to_float(i); // int -> float
extern fun to_int(f);   // float -> int

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

//--------------------------------------------------------------------------
// Helper float constants (since we can't embed "0.0" or "0.01" directly):
//--------------------------------------------------------------------------
fun fzero() {
    // float 0.0
    return to_float(0);
}

fun fone() {
    // float 1.0
    return to_float(1);
}

fun ftiny() {
    // float 0.000001
    // = 1 / 1000000 in float
    let one = fone();
    let million = to_float(1000000);
    return fdiv(one, million);
}

fun fpoint01() {
    // float 0.01 = 1 / 100 in float
    let one = fone();
    let hundred = to_float(100);
    return fdiv(one, hundred);
}

//--------------------------------------------------------------------------
// Access each body's data in the array.
//
// We store 5 floats per body in the array:
//   index: 0 -> x
//          1 -> y
//          2 -> vx
//          3 -> vy
//          4 -> m
//
// The array is of size nbodies * 5. We do integer ops for addressing,
// float ops for reading/writing the data.
//--------------------------------------------------------------------------
fun body_get_x(bodies, nbodies, stride, i) {
    let off = add(mul(i, stride), 0); // int offset
    return deref(idx(bodies, off));   // float
}

fun body_get_y(bodies, nbodies, stride, i) {
    let off = add(mul(i, stride), 1);
    return deref(idx(bodies, off));   // float
}

fun body_get_vx(bodies, nbodies, stride, i) {
    let off = add(mul(i, stride), 2);
    return deref(idx(bodies, off));   // float
}

fun body_get_vy(bodies, nbodies, stride, i) {
    let off = add(mul(i, stride), 3);
    return deref(idx(bodies, off));   // float
}

fun body_get_m(bodies, nbodies, stride, i) {
    let off = add(mul(i, stride), 4);
    return deref(idx(bodies, off));   // float
}

// Setters
fun body_set_x(bodies, nbodies, stride, i, val) {
    let off = add(mul(i, stride), 0);
    *idx(bodies, off) = val;  // val is float
    return val;
}

fun body_set_y(bodies, nbodies, stride, i, val) {
    let off = add(mul(i, stride), 1);
    *idx(bodies, off) = val;
    return val;
}

fun body_set_vx(bodies, nbodies, stride, i, val) {
    let off = add(mul(i, stride), 2);
    *idx(bodies, off) = val;
    return val;
}

fun body_set_vy(bodies, nbodies, stride, i, val) {
    let off = add(mul(i, stride), 3);
    *idx(bodies, off) = val;
    return val;
}

fun body_set_m(bodies, nbodies, stride, i, val) {
    let off = add(mul(i, stride), 4);
    *idx(bodies, off) = val;
    return val;
}

//--------------------------------------------------------------------------
// A small float "square" function: square(x) = x*x in float
//--------------------------------------------------------------------------
fun fsquare(x) {
    return fmul(x, x);
}

//--------------------------------------------------------------------------
// calc_force(): Compute the gravitational force of body j on body i.
//
// Force = G * (m_i * m_j) / r^2   (then direction scaled by dx/r, dy/r)
// We skip G=1 or incorporate it as 1, and approximate 1/r^3 without a sqrt
// to avoid mixing or implementing custom sqrt.
//
// We'll store the result in out_fx, out_fy (both are pointers to float).
//--------------------------------------------------------------------------
fun calc_force(bodies, nbodies, stride, i, j, out_fx, out_fy) {
    let xi  = body_get_x(bodies, nbodies, stride, i);  // float
    let yi  = body_get_y(bodies, nbodies, stride, i);
    let xj  = body_get_x(bodies, nbodies, stride, j);
    let yj  = body_get_y(bodies, nbodies, stride, j);
    let mj  = body_get_m(bodies, nbodies, stride, j);

    // dx, dy in float
    let dx = fsub(xj, xi);
    let dy = fsub(yj, yi);

    // r^2 = dx^2 + dy^2
    let r2 = fadd(fsquare(dx), fsquare(dy));

    // Avoid dividing by near-zero (if bodies overlap)
    let tiny = ftiny();
    // if r2 < tiny, set r2 = tiny
    if (flt(r2, tiny)) {
        r2 = tiny;
    }

    // approximate 1 / r^3 ~ 1 / (r2^(3/2)) 
    // We'll just do 1 / (r2*r2) = 1 / r2^2 as a rough approximation
    // float_one = 1.0
    let float_one = fone();
    let r2r2      = fmul(r2, r2);       // r2^2
    let inv_r3    = fdiv(float_one, r2r2);

    // Force from j on i = m_j * dx * (1 / r^3)  (for x-component)
    //                     m_j * dy * (1 / r^3)  (for y-component)
    let fx = fmul(mj, fmul(dx, inv_r3));
    let fy = fmul(mj, fmul(dy, inv_r3));

    // Write to out_fx, out_fy
    *out_fx = fx;
    *out_fy = fy;

    return 0; // an int
}

//--------------------------------------------------------------------------
// update_bodies():
// 1) Accumulate the net force on each body from all others.
// 2) Forward Euler integration:
//
//    vx[i] += (Fx[i] / m[i]) * dt
//    vy[i] += (Fy[i] / m[i]) * dt
//    x[i]  += vx[i] * dt
//    y[i]  += vy[i] * dt
//--------------------------------------------------------------------------
fun update_bodies(bodies, nbodies, stride, dt) {
    // We'll store net force in a local array of nbodies x 2 (Fx, Fy), all floats
    let forces = malloc(mul(nbodies, 2)); // each cell is a float

    // Initialize forces to 0.0 for each body
    let i = 0; // int
    let f0_ = fzero(); 
    while (lt(i, nbodies)) {
        // Fx
        *idx(forces, add(mul(i, 2), 0)) = f0_;
        // Fy
        *idx(forces, add(mul(i, 2), 1)) = f0_;
        i = add(i, 1);
    }

    // For each pair (i, j), compute force j->i, accumulate
    i = 0;
    while (lt(i, nbodies)) {
        let j = 0;
        while (lt(j, nbodies)) {
            if (neq(i, j)) {
                // We'll store the partial force in small pointers
                let fx_addr = malloc(1);  // storing 1 float
                let fy_addr = malloc(1);

                calc_force(bodies, nbodies, stride, i, j, fx_addr, fy_addr);

                // read current net force
                let cur_fx = deref(idx(forces, add(mul(i, 2), 0))); // float
                let cur_fy = deref(idx(forces, add(mul(i, 2), 1))); // float

                // add in the new partial force
                let new_fx = fadd(cur_fx, deref(fx_addr));
                let new_fy = fadd(cur_fy, deref(fy_addr));

                // store back
                *idx(forces, add(mul(i, 2), 0)) = new_fx;
                *idx(forces, add(mul(i, 2), 1)) = new_fy;
            }
            j = add(j, 1);
        }
        i = add(i, 1);
    }

    // Now integrate to update velocities and positions
    i = 0;
    while (lt(i, nbodies)) {
        let m   = body_get_m (bodies, nbodies, stride, i);  // float
        let vx  = body_get_vx(bodies, nbodies, stride, i);
        let vy  = body_get_vy(bodies, nbodies, stride, i);
        let x   = body_get_x (bodies, nbodies, stride, i);
        let y   = body_get_y (bodies, nbodies, stride, i);

        let fx  = deref(idx(forces, add(mul(i, 2), 0)));    // float
        let fy  = deref(idx(forces, add(mul(i, 2), 1)));

        // ax = fx / m
        let ax = fdiv(fx, m);
        let ay = fdiv(fy, m);

        // vx <- vx + ax * dt
        let vx_new = fadd(vx, fmul(ax, dt));
        // vy <- vy + ay * dt
        let vy_new = fadd(vy, fmul(ay, dt));

        // x <- x + vx_new * dt
        let x_new = fadd(x, fmul(vx_new, dt));
        let y_new = fadd(y, fmul(vy_new, dt));

        // store new values
        body_set_vx(bodies, nbodies, stride, i, vx_new);
        body_set_vy(bodies, nbodies, stride, i, vy_new);
        body_set_x (bodies, nbodies, stride, i, x_new);
        body_set_y (bodies, nbodies, stride, i, y_new);

        i = add(i, 1);
    }

    return 0;
}

//--------------------------------------------------------------------------
// print_bodies(): Show each body's position, velocity, and mass.
//   We'll just convert floats to int for printing with puti(...).
//   This is purely for demonstration, so you won't see decimal fractions.
//--------------------------------------------------------------------------
fun print_bodies(bodies, nbodies, stride) {
    let i = 0;
    while (lt(i, nbodies)) {
        puts("Body ");
        puti(i); 
        puts(": x=");
        // Convert float x to int for puti
        let x_i = body_get_x(bodies, nbodies, stride, i);
        putf(x_i);

        puts(", y=");
        let y_i = body_get_y(bodies, nbodies, stride, i);
        putf(y_i);

        puts(", vx=");
        let vx_i = body_get_vx(bodies, nbodies, stride, i);
        putf(vx_i);

        puts(", vy=");
        let vy_i = body_get_vy(bodies, nbodies, stride, i);
        putf(vy_i);

        puts(", m=");
        let m_i  = body_get_m(bodies, nbodies, stride, i);
        putf(m_i);

        putln();
        i = add(i, 1);
    }
    putln();
    return 0;
}

//--------------------------------------------------------------------------
// three_body() - sets up 3 bodies, runs a basic simulation.
//--------------------------------------------------------------------------
fun three_body() {
    // We'll have 3 bodies, each with 5 float attributes
    let nbodies = 3;       // int
    let stride  = 5;       // int
    let total_size = mul(nbodies, stride);
    let bodies = malloc(total_size); // all floats

    // Initialize the bodies with some positions, velocities, masses in float
    // Body 0
    body_set_x (bodies, nbodies, stride, 0, fzero()); // x=0
    body_set_y (bodies, nbodies, stride, 0, fzero()); // y=0
    body_set_vx(bodies, nbodies, stride, 0, fzero()); // vx=0
    body_set_vy(bodies, nbodies, stride, 0, to_float(1)); // vy=1
    body_set_m (bodies, nbodies, stride, 0, to_float(10)); // mass=10

    // Body 1
    body_set_x (bodies, nbodies, stride, 1, to_float(5));  // x=5
    body_set_y (bodies, nbodies, stride, 1, fzero());      // y=0
    body_set_vx(bodies, nbodies, stride, 1, fzero());      // vx=0
    body_set_vy(bodies, nbodies, stride, 1, to_float(-1)); // vy=-1
    body_set_m (bodies, nbodies, stride, 1, to_float(10)); // mass=10

    // Body 2
    body_set_x (bodies, nbodies, stride, 2, fzero());      // x=0
    body_set_y (bodies, nbodies, stride, 2, to_float(7));  // y=7
    body_set_vx(bodies, nbodies, stride, 2, to_float(-1)); // vx=-1
    body_set_vy(bodies, nbodies, stride, 2, fzero());      // vy=0
    body_set_m (bodies, nbodies, stride, 2, to_float(5));  // mass=5

    // Print initial
    puts("Initial State:\n");
    print_bodies(bodies, nbodies, stride);

    // Simulation parameters:
    let dt = fpoint01();  // 0.01 (float)
    let steps = 1000;     // int

    let step = 0;
    while (lt(step, steps)) {
        update_bodies(bodies, nbodies, stride, dt);
        step = add(step, 1);
    }

    // Final
    puts("Final State after ");
    puti(steps);
    puts(" steps:\n");
    print_bodies(bodies, nbodies, stride);

    return 0;
}

//--------------------------------------------------------------------------
// main()
//--------------------------------------------------------------------------
fun main() {
    three_body();
    return 0;
}

main();