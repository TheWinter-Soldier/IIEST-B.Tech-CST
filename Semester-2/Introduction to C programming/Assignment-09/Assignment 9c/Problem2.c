#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[50];
    int roll;
    float percentage;
};

int main() {
    struct Student *A; 
    int i,n; 
    char temp;

    printf("Give the number of students whose data will be stored: ");
    scanf("%d",&n);

    A = (struct Student *)calloc(n,sizeof(struct Student));

    printf("Enter the NAME, ROLL & PERCENTAGE of %d students:\n",n);
    printf("[Give the name, Press Enter. ");
    printf("Give the Roll and Percentage seperated by space.]\n");
    for(int i=0;i<n;i++) {
        printf("Data for %d",i+1);
        if(i%10 == 0) printf("st ");
        else if(i%10 == 1) printf("nd ");
        else if(i%10 == 2) printf("rd ");
        else printf("th ");
        printf("student: ");
        scanf("%c",&temp);
        gets((A+i)->name);
        scanf("%d %f",(&(A+i)->roll),&((A+i)->percentage));  
    }

    printf("Name\t\tRoll\tPercentage\n");
    for(i=0;i<n;i++) {
        printf("%s\t%d\t%f\n",(A+i)->name,(A+i)->roll,(A+i)->percentage);
    }

    return 0;
}