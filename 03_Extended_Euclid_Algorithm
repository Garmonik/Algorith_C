#include <stdio.h>

typedef long long kek;

struct gcd_params_t {
    kek d, u, v;
};

struct gcd_params_t gcd_result(kek d, kek u, kek v) {
    struct gcd_params_t ret = {d, u, v};
    return ret;
}

struct gcd_params_t gcd(kek m, kek n) {
    kek a = m;
    kek b = n;
    kek u_old = 1, u = 0, v_old = 0, v = 1;

    while (b != 0){
        kek tu, tv, q, r;

        q = a / b; r = a % b;
        a = b; b = r;
        tu = u; tv = v;

        u = u_old - q * u;
        v = v_old - q * v;

        u_old = tu; v_old = tv;
    }

    return gcd_result(a, u_old, v_old);
}

int main() {
    kek a, b;
    struct gcd_params_t d;
    scanf("%lld %lld", &a, &b);
    d = gcd(a, b);
    printf("%lld %lld %lld\n", d.u, d.v, d.d);
    return 0;
}
