#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int a, b, c=0; 
    char Num1[20], Num2[20], Sum[20]="\0";

    printf("Give first integer: ");
	gets(Num1);
    printf("Give second integer: ");
	gets(Num2);
    
    a = atoi(Num1);
    b = atoi(Num2);

    c=a+b;

    itoa(c,Sum,10);
    printf("The sum of the integers is %s.\n",Sum);

    return 0;
}