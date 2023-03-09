#include <stdio.h>

struct Complex {
    int real;
    int imaginary;
};

struct Complex sum(struct Complex a,struct Complex b) {
    struct Complex s;

    s.real = a.real + b.real;
    s.imaginary = a.imaginary + b.imaginary;
    
    return s;
}

int main() {
    struct Complex N1,N2;
    printf("Give the real & imaginary part of 1st no. respectively: ");
    scanf("%d %d",&N1.real,&N1.imaginary);
    printf("Give the real & imaginary part of 2nd no. respectively: ");
    scanf("%d %d",&N2.real,&N2.imaginary);

    printf("Sum = %d + i(%d)\n",sum(N1,N2).real,sum(N1,N2).imaginary);

    return 0;
}