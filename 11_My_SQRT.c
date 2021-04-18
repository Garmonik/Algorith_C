#include <stdio.h>
#include <math.h>

#define Delta 1e-10

int main(){
    double num,sqr;
    double ob = 0, un = 0, m = 0;

    scanf("%lf",&num);

    ob = num;
    m = (un + ob) / 2;

    do{
        if(m * m > num){
            ob = m;
            m = (un + ob)/2;
        }
        else{
            un = m;
            m = (un + ob)/2;
        }
        sqr = m * m;
    }
    while((fabsf(num-sqr) >= Delta));

    printf("%f\n", m);
}
