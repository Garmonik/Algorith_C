#include <stdio.h>

struct gcd_params_t {
    int d, u, v;
};

struct gcd_params_t gcd_result(int d, int u, int v) {
    struct gcd_params_t ret = {d, u, v};
    return ret;
}

struct gcd_params_t gcd(int m, int n) {
    int a = m;
    int b = n;
    int u_old = 1, u = 0, v_old = 0, v = 1;

    while (b != 0){
        int tu, tv, q, r;

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
    int a, b;
    struct gcd_params_t d;
    scanf("%d %d", &a, &b);
    d = gcd(a, b);
    printf("%d %d %d\n", d.u, d.v, d.d);
    return 0;
}