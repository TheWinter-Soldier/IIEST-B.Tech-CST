#include <stdio.h>
#include <string.h>

int main() {
  	char word[100];
  	int i, flag=0;

	printf("Enter any word: ");
	gets(word);
    
	for(i=0;word[i] != '\0';i++) {
        if((word[i]>='a') && (word[i]<='z')) {
            word[i] = word[i] - 32;
        }
    }

  	for(i=0;word[i] != '\0';i++) {
		if(word[i] != word[strlen(word)-i-1]) {
			flag = 1;
			break;	
		} 
	}

	if(flag == 0) printf("%s is a Palindrome String.\n",word);
	else printf("%s is Not a Palindrome String.\n",word);
	
    return 0;
}