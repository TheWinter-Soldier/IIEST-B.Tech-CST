#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main() { 
    FILE *fp; 
    int n, i; 
    char C='\0';

    fp = fopen("File_for_Problem1.txt","w");
    if(fp==NULL) {
        printf("Cannot open file.\n");
        exit(0);
    }

    printf("Give the number of characters to print in file: ");
    scanf("%d",&n);
    for(i=0;i<n;i++) {
        printf("Give the ");
        if(i==0) printf("first ");
        else if(i==1) printf("second ");
        else if(i==2) printf("third ");
        else printf("%dth ",i+1);
        printf("character: ");
        C = getch();
        fprintf(fp,"%c",C);
    }

    fclose(fp);

    fp = fopen("File_for_Problem1.txt","r");

    printf("\nThe characters written in the file are: ");
    char x = fgetc(fp);
    while(x != EOF) {
        printf("%c",x);
        x = fgetc(fp);
    }

    fclose(fp);

    return 0;
}