#include <stdio.h>
#include <locale.h>

// псевдоним для целочисленного типа с которым будем работать
//typedef char itype;
//typedef short int itype;
//typedef int itype;
//typedef long int itype;
typedef long long int itype;

typedef enum { GN_OK = 0, GN_NEG, GN_ILL, GN_LONG } GNENUM;

GNENUM get_num(itype *num){
    *num = 0;
    itype prevnum = 0;
    int ch;
    
    // анализируем первый символ
    ch = getchar();
    
    if (ch == EOF)
        return GN_ILL;
        
    if (ch == '-'){
        // анализируем второй символ для правильной диагностики ситуации
        int ch2 = getchar();
        
        if (ch2 >= '0' && ch2 <= '9')
            return GN_NEG;
        else
            return GN_ILL;
    }
    
    if (ch != '+')      // игнорируем символ '+'
        ungetc(ch, stdin);  // возвращаем первый символ обратно в буфер ввода

    while ((ch = getchar()) != EOF){  // конец ввода по ошибке файла
        if (ch == '\n')                // или по символу конца строки
            break;
            
        if (ch < '0' || ch > '9')   // найден нецифровой символ
            return GN_ILL;
            
        *num = *num * 10 + (ch - '0');
        
        if (*num < prevnum)     // проверка на переполнение
            return GN_LONG;
            
        prevnum = *num;
    }
    return GN_OK;
}

void toBin(itype n){
    if (n > 1)
        toBin(n / 2);
    putchar(n % 2 + '0');
}


int main(){

    setlocale(LC_ALL, "Russian");

    itype number;

    printf("Enter a positive integer no longer than %u bits: ", (unsigned int)sizeof(itype)* 8);
    GNENUM gn_ret = get_num(&number);
    if (gn_ret != GN_OK){
        switch (gn_ret)
        {
            case GN_NEG:
                printf("\nNegative number entered.\n");
                break;
            case GN_ILL:
                printf("\nInvalid number format.\n");
                break;
            case GN_LONG:
                printf("Too large number entered.\n");
                break;
            default:
                printf("Error\n");
                break;
        }
        return 1;
    }

    // вывод в максимально длинном целочисленном типе
    printf("Enter \ndecimal:\t%lld \nhexadecimal:\t%llX \nbinary:\t", (long long int)number, (long long int)number);
    // вывод двоичного представления
    toBin(number);
    printf("\n");

    return 0;
}
