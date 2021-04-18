#include <stdio.h>

void factorize( int n, int* a, int* b )
{
    int i = 2;
    if (n == 1){
        *(a) = *(b) = 1;
    }
    while(i <= (n/2)){
        if (n % i == 0){
            *(b) = i;
            *(a) = n / i;
            break;
        }
        else if (n % i != 0){
            *(a) = 1;
            *(b) = n;
        }
        i++;
    }

}

int main(){
    int a = 0, b = 0, n = 0;
    scanf("%d", &n);
    factorize(n, &a, &b);
    printf("%d   %d", a, b);
    return 0;
}
