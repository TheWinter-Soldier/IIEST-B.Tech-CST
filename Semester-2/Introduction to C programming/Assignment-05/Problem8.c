#include<stdio.h>

int main() {
    int c;
    printf("Enter any character: ");

    while((c = getchar()) != 'q') {
        if(c != '\n') {
            printf("The ASCII value of this Character is %d.\n",c);
            printf("Enter a character again: ");
        }
    }

    return 0;
}