#include <stdio.h>
#include <string.h>

int main() {
    char A[10][50], temp[50]="\0"; 
    int i,j;

    for(i=0;i<10;i++) {
        printf("Give the %d",i+1);
        if(i==0) printf("st ");
        else if(i==1) printf("nd ");
        else if(i==2) printf("rd ");
        else printf("th ");
        printf("Name: ");
        gets(A[i]);
    }

    for(i=0;i<10;i++) {
        for(j=0;j<10-i-1;j++) {
            if(strcmp(A[j],A[j+1])>0) {
                strcpy(temp,A[j]);
                strcpy(A[j],A[j+1]);
                strcpy(A[j+1],temp);
            }
        }
    }

    printf("The names when arranged in ascendence:\n");
    for(i=0;i<10;i++) {
        printf("%s\n",A[i]);
    }

    return 0;
}