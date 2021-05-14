#include <stdio.h>

int is_prime(int n){
    if (n > 1)
    {
        for (int i = 2; i < n; i++)
            if (n % i == 0)
                return 0;
        return 1;
    }
    else
        return 0;
}

int main(){
    int a = 0, b = 0, n = 0;
    scanf("%d", &n);
    int c = is_prime(n);
    if (c == 1) printf("Number is prime!");
    else printf("Numeber is not prime!");
    return 0;
}
