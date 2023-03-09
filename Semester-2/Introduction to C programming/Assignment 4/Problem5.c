#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;
    printf("Enter any Character: ");
    scanf("%c",&ch);

    if(isalpha(ch)) {
        if(isupper(ch)) printf("The character you entered is a Capital Letter.\n");
        else printf("The character you entered is a Small Letter.\n");
    }
    else if(isdigit(ch)) printf("The character you entered is a Number.\n");
    else printf("The character you entered is a Special character.\n");
    
    return 0;
}