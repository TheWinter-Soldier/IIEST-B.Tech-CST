#include <stdio.h>

int main() {
    int Year, Days=0, i;
    printf("Enter any year and we will tell you what day it be in 1st january: ");
    scanf("%d",&Year);
    
    for(i=1900;i<Year;i++) {
        if(i%4==0) {
            if(i%100==0) {
                if(i%400==0) Days+=366;
                else Days+=365;
            }
            else Days+=366;
        }
        else Days+=365;
    }

    printf("1st January,%d",Year);
    if(Year>2021) printf(" will be");
    else printf(" was");

    if(Days%7==0) printf(" Monday.\n");
    else if(Days%7==1) printf(" Tuesday.\n");
    else if(Days%7==2) printf(" Wednesday.\n");
    else if(Days%7==3) printf(" Thursday.\n");
    else if(Days%7==4) printf(" Friday.\n");
    else if(Days%7==5) printf(" Saturday.\n");
    else printf(" Sunday.\n");

    return 0;
}