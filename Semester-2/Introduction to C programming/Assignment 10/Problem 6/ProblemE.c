#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp1, *fp2; 
    char str[100], ch, s[10]; 
    int del, c=1;

    printf("Enter the line-number you want to replace: ");
    scanf("%d",&del);
    getchar();
    printf("Enter the replacement sentence: ");
    gets(str);

    fp1 = fopen("File1_for_ProblemE.txt","r");

    printf("\nFile before replacing the given line:\n");
    while(fgets(s,9,fp1) != NULL) printf("%s",s);

    fclose(fp1);

    printf("\n");

    fp1 = fopen("File1_for_ProblemE.txt","r");
    fp2 = fopen("File2_for_ProblemE.txt","w");

    ch = fgetc(fp1);
    while((ch != EOF) && (del!=1)) {
        if(del==c) {
            fputc(ch,fp2);
            break;;
        }
        if(ch=='.') {
            c++;
        }
        fputc(ch,fp2);
        ch = fgetc(fp1);
    }

    fclose(fp1);
    fclose(fp2);

    if(del==1) fp2 = fopen("File2_for_ProblemE.txt","w");
    else fp2 = fopen("File2_for_ProblemE.txt","a");

    fputs(str,fp2);

    fclose(fp2); 

    fp2 = fopen("File2_for_ProblemE.txt","a");
    fp1 = fopen("File1_for_ProblemE.txt","r");

    ch=fgetc(fp1);
    c=0;
    while(ch != EOF) {
        if(c>=del) {
            fputc(ch,fp2);
        }
        if(ch=='.') {
            c++;
        }
        ch=fgetc(fp1);
    }

    fclose(fp2);
    fclose(fp1);
    
    fp2 = fopen("File2_for_ProblemE.txt","r");

    printf("\nFile after replacing the given line:\n");
    while(fgets(s,9,fp2) != NULL) printf("%s",s);
        
    fclose(fp2);

    printf("\n");

    return 0;
}