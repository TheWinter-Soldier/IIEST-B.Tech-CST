#include <stdio.h>

struct Student {
    char name[50];
    int roll;
    float percentage;
};

int main() {
    struct Student A[10]; 
    char temp;

    printf("Enter the NAME, ROLL & PERCENTAGE of 10 students:\n");
    printf("[Give the name, Press Enter. ");
    printf("Give the Roll and Percentage seperated by space.]\n");
    for(int i=0;i<10;i++) {
        printf("Data for student %d: ",i+1);
        gets(A[i].name);
        scanf("%d %f",&A[i].roll,&A[i].percentage);
        scanf("%c",&temp);  
    }

    printf("\nName\t\tRoll\tPercentage\n");
    float per=A[0].percentage;
    int i, p=0;
    for(i=0;i<10;i++) {
        printf("%s\t%d\t%f\n",A[i].name,A[i].roll,A[i].percentage);
        if(A[i].percentage > per) {
            per = A[i].percentage;
            p=i;
        }
    }

    printf("Record of student with highest percentage:\n");
    printf("%s, Roll - %d, %f marks\n",A[p].name,A[p].roll,A[p].percentage);

    return 0;
}