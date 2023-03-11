#include <stdio.h>
#include <ctype.h>

int T() {
    static int c=-1;

    c+=1;

    return c;
}

int main() {
  	char word[100], Initials[100]="\0";
  	int i, count=0;

	printf("Give names to print them with initials: ");
	gets(word);

    for(i=0;word[i] != '\0';i++) {
        if(word[i]==' ') count=i;
    }

    if(count==0) {
        word[0] = toupper(word[0]);

        printf("The only name is %s.\n",word);
    }
    else {
        Initials[T()] = toupper(word[0]);
        Initials[T()] = '.';
        Initials[T()] = ' ';

	    for(i=0;i<count;i++) {
            if(word[i]==' ') {
                Initials[T()] = toupper(word[i+1]);
                Initials[T()] = '.';
                Initials[T()] = ' ';
            }
            continue;
        }
    
        Initials[T()] = toupper(word[count+1]);
        for(i = count+2;word[i] != '\0';i++) {
            Initials[T()] = word[i];
        }
    
        printf("The initials of the given name is %s.\n",Initials);
    }

    return 0;
}