#include <stdio.h>

int main() {
    double GrossSalary, BasicSalary, HRA, DA, PF, NetSalary; 
    int PTAX=200;
    printf("Enter your Basic Salary: ");
    scanf("%lf", &BasicSalary);

    HRA = (3.0*(BasicSalary/10.0));
    DA = (119.0*(BasicSalary/100.0));
    GrossSalary = BasicSalary+DA+HRA;
    PF = (12.0*(BasicSalary/100.0));
    NetSalary = (GrossSalary-(PF+PTAX));

    printf("Your Net Salary is %lf.\n",NetSalary);
    
    return 0;
}