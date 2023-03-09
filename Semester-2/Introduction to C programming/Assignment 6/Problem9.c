#include <stdio.h>
#include <math.h>

void DecimalToBinary() {
    int a[50], Number, i, j;
    printf("Please Enter the Number You want to Convert: ");
    scanf("%d",&Number);
    
    for(i=0;Number>0;i++) {
        a[i] = Number%2;
        Number /= 2;
    }
    
    printf("Binary representation of the Given Number = ");
    for(j=i-1;j>=0;j--)  {
        printf("%d",a[j]);
    }
    printf("\n");
}

void BinaryToDecimal() {
    int a, Number, i; 
    double Result=0.0;
    printf("Please Enter the Number You want to Convert: ");
    scanf("%d",&Number);
    
    for(i=0;Number>0;i++) {
        a = Number%10;
        Number /= 10;
        Result += (a*pow(2,i));
    }
    
    printf("Decimal representation of the Given Number = %.0lf.",Result);
    printf("\n");
}

int main() {
    int Choice, Count=0;
    printf("This is a menu driven program for inter-conversion of numbers.\n");
    
    while(1) {
        Count++;
        printf("\n1. Convert Binary to Decimal\n2. Convert Decimal to Binary\n3. Exit the Program.\n");
        printf("\nEnter your Choice");
        if(Count>1) printf(" again");
        printf(": ");
        scanf("%d",&Choice);

        switch(Choice) {
            case 1:
            BinaryToDecimal();
            break;
            
            case 2:
            DecimalToBinary();
            break;
            
            case 3:
            printf("Program terminated successfully.\n\n");
            return 0;
            
            default:
            printf("\nPlease Select 1-3 option only ----\n");
        }
    }
}