#include <stdio.h>
int main() {
    unsigned int a,b,m,n,i;
    printf("Числовой промежуток: ");
    scanf("%d%d",&a,&b);
    printf("Минимальное количество делителей: ");
    scanf("%d",&n);
    while (a <= b) {
        m = 0;
        for (i=1; i<=a; i++)
            if (a%i == 0) m += 1;
        if (m >= n) {
            printf("%d: ", a);
            for (i=1; i<=a; i++)
                if (a%i == 0) printf("%d ", i);
            printf("\n");
        }
        a += 1;
    }
}
