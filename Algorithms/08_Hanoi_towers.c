#include <stdio.h>

void hanoi(int n, int i, int k){
    if(n == 1)
    printf("Move disk 1 from pin %d to %d.\n", i, k);
    else{
        int tmp = 6 - i - k;

        hanoi(n - 1, tmp, k);

        printf("Move disk %d from pin %d to %d.\n", n, i, k);
        hanoi(n - 1, tmp, k);
    }
}

int main(){
    int n, i, k;
    scanf("%d", &n);
  
    hanoi(n, 1, 2);
    return 0;
}
