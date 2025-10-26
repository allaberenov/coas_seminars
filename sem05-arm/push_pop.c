#include <stdio.h>

extern int pop();
extern void push(int i);

int main(){
    push(3);
    int a = pop();
    printf("%d", a);
}