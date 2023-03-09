#include <stdio.h>
#include <conio.h>

int main() { 
    FILE *fp; 
    int n, i; 
    char A[10][50], C='\0';

    fp = fopen("Common_file.txt","w");

    if(fp==NULL) {
        printf("Cannot open file.\n");
    }

    printf("Give the number of lines to print in file: ");
    scanf("%d",&n);
    for(i=0;i<n;i++) {
        printf("Give ");
        if(i==0) printf("first ");
        else if(i==1) printf("second ");
        else if(i==2) printf("third ");
        else printf("%dth ",i+1);
        printf("sentence: ");
        if(i==0) scanf("%c",&C);
        gets(A[i]);
        fprintf(fp,"%s\n",A[i]);
    }

    fclose(fp);

    return 0;
}