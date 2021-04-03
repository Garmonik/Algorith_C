#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned long long a, b;
    int c = 0;
    unsigned long long tmp = 0;

    c = scanf("%llu %llu", &a, &b);
    assert(c == 2);

    while (a > 0) {
        if (b > a) {
            tmp = a;
            a = b;
            b = tmp;
        }
        a %= b;
    }
    printf("%llu", b);
}
