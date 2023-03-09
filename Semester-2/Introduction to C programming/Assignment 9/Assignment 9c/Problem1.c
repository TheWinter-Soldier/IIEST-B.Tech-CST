#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[50];
    int roll;
    float percentage;
};

int main() {
    struct Student *A;

    A = (struct Student *)calloc(1,sizeof(struct Student));

    printf("Enter the NAME, ROLL & PERCENTAGE of a student:\n");
    printf("[Give the name, Press Enter. ");
    printf("Give the Roll and Percentage seperated by space.]\n");

    printf("Data for student: ");
    gets(A->name);
    scanf("%d %f",&A->roll,&A->percentage);   


    printf("\nName\t\tRoll\tPercentage\n");
    printf("%s\t%d\t%f\n",A->name,A->roll,A->percentage);

    return 0;
}