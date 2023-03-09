#include <stdio.h>

struct Complex {
    int real;
    int imaginary;
};

void Sum(struct Complex a,struct Complex b) {
    struct Complex s;

    s.real = a.real + b.real;
    s.imaginary = a.imaginary + b.imaginary;

    printf("Sum = %d + i(%d)\n",s.real,s.imaginary);
}

int main() {
    struct Complex N1,N2;
    printf("Give the real & imaginary part of 1st no. respectively: ");
    scanf("%d %d",&N1.real,&N1.imaginary);
    printf("Give the real & imaginary part of 2nd no. respectively: ");
    scanf("%d %d",&N2.real,&N2.imaginary);

    Sum(N1,N2);

    return 0;
}