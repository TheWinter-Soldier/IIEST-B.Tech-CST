#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp1, *fp2; 
    char ch, s[10], s1[10]="f1.txt", s2[10]="tf.txt"; 
    int del, c=1;

    printf("There are 5 lines in the file.\n");
    printf("Enter the line-number you want to delete: ");
    scanf("%d",&del);

    fp1 = fopen("File1_for_ProblemD.txt","r");

    printf("\nFile before deleting the line :\n");
    while(fgets(s,9,fp1) != NULL) printf("%s",s);

    fclose(fp1);

    printf("\n");

    fp1=fopen("File1_for_ProblemD.txt","r+");
    fp2=fopen("File2_for_ProblemD.txt","w");

    ch=fgetc(fp1);
    while(ch != EOF) {
        if(ch == '.') c++;
        if(del != c) fputc(ch,fp2);
        ch=fgetc(fp1);
    }

    fclose(fp1);
    fclose(fp2);

    remove(s1);
    rename(s2,s1);

    fp2=fopen("File2_for_ProblemD.txt","r");

    printf("\nFile after deleting the given line:\n");
    while(fgets(s,9,fp2)!=NULL) printf("%s",s);

    fclose(fp2);

    printf("\n");

    return 0;
}