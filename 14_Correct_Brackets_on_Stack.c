#include <stdio.h>

#define MAX_STACK 1024
char stack[MAX_STACK];
int stack_ptr = 0;

// Прототипы
int check(char* s);
//char check_rec(char** s);
int push(char x);
int pop(char* x);

int main(){
    char buffer[8192];
    char* s = fgets(buffer, sizeof(buffer), stdin);

        if(!check(s))
            printf("OK\n");
        else
            printf("NOT OK\n");

    return 0;
}

int check(char* s){
    int err = 0;
    char x;

    while (*s){
        switch (*s){
            case '(':
                err = push(')'); break;
            case '{':
                err = push('}'); break;
            case '[':
                err = push(']'); break;
            case '<':
                err = push('>'); break;
            case ')': case ']': case '}': case'>':
                    if((err = pop(&x)) || x != *s)
                        return -1;
                    break;
            default:
                break;
        }
        if(err) return -1;
        s++;
    }
    if(!pop(&x)) return -1;
    return 0;
}

int push(char x){
    if(stack_ptr >= MAX_STACK)
        return -1;

    stack[stack_ptr++] = x;
    return 0;
}

int pop(char* x){
    if (stack_ptr <= 0)
        return -1;

    *x = stack[--stack_ptr];
    return 0;
}
