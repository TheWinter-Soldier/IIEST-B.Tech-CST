#include <stdio.h>

void Concatenator(char Str1[], char Str2[]) {
    int i=0, j;

    while(Str1[i] != '\0') {
        i++;
    }

    j=0;
    while(Str2[j] != '\0') {
        Str1[i] = Str2[j];

        i++;
        j++;
    }

    Str1[i] = '\0';

    printf("%s.\n",Str1);
}

int main() {
    char str1[100], str2[100];
    printf("Enter first string: ");
    gets(str1);
    printf("Enter second string: ");
    gets(str2);

    printf("Concatenated string is ---- ");
    Concatenator(str1,str2);
    
    return 0;
}