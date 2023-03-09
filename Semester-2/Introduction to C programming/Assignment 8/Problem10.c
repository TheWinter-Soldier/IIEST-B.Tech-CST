#include <stdio.h>

struct Complex {
    int real;
    int imaginary;
};

struct number {
    struct Complex comp;
    int Real;
};

struct Complex sum(struct Complex a,struct Complex b) {
    struct Complex s;

    s.real = a.real + b.real;
    s.imaginary = a.imaginary + b.imaginary;
    
    return s;
}

int main() {
    struct number Num[3];
    for(int i=0;i<3;i++) {
        printf("Enter the real part of complex no. %d: ",i+1);
        scanf("%d",&Num[i].comp.real);
        printf("Enter the imaginary part of complex no. %d: ",i+1);
        scanf("%d",&Num[i].comp.imaginary);
        printf("Enter the real no. %d: ",i+1);
        scanf("%d",&Num[i].Real);
    }
    
    printf("Pure real numbers are: ");
    for(int i=0;i<3;i++) {
        printf("%d, ",Num[i].Real);
    }
    printf("\n");
    printf("Complex numbers are: ");
    for(int i=0;i<3;i++) {
        printf("%d + (%d)i, ",Num[i].comp.real,Num[i].comp.imaginary);
    }
    
    printf("\n");

    return 0;
}