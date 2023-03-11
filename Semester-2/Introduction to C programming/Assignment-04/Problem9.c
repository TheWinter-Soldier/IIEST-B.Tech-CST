#include <stdio.h>

int main() {
    float Maths, Physics, Chemistry, Total, Percentage;
    printf("Enter the marks you obtained in three subjects (out of 100 each): ");
    scanf("%f %f %f",&Physics,&Chemistry,&Maths);

    Total = Physics+Chemistry+Maths;
    Percentage = Total/3;
    printf("You scored %f%% marks in the examination.\n",Percentage);
    if(Percentage>=34) {
        if(Percentage>=34 && Percentage<45) {
            printf("Congratulations! You have passed with 3rd Division.\n");
        }
        else if(Percentage>=45 && Percentage<60) {
            printf("Congratulations! You have passed with 2nd Division.\n");
        }
        else if(Percentage>=60) {
            printf("Congratulations! You have passed with 1st Division.\n");
        }
    }
    else printf("Oops! You failed.\n");

    return 0;
}