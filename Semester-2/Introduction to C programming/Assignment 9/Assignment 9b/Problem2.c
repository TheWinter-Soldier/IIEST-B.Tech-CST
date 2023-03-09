#include <stdio.h>
#include <stdlib.h>

struct Complex {
    int real;
    int imaginary;
};

int main() {
    struct Complex *C; 
    int n, i;

    printf("Give the number of complex numbers you want to store: ");
    scanf("%d",&n);

    C = (struct Complex *)calloc((n+1),sizeof(struct Complex));

    for(i=0;i<n;i++) {
        printf("Give the real & imaginary part of the %d",i+1);
        if(i==0) printf("st ");
        else if(i==1) printf("nd ");
        else if(i==2) printf("rd ");
        else printf("th ");
        printf("Complex-number respectively: ");
        scanf("%d %d",&((C+i)->real),&((C+i)->imaginary));
    }

    for(i=0;i<n;i++) {
        (C+n)->real += (C+i)->real;
        (C+n)->imaginary += (C+i)->imaginary;
    }

    printf("The sum as stored in %dth position is %d + i(%d).\n",n+1,(C+i)->real,(C+i)->imaginary);
    
    return 0;
}