/* Read in two integers , add them and display the answer */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
int this_is_a_number1, this_is_a_number2, total;
printf("Please enter an integer number:\n ");
/* read number in */
if (scanf("%d", &this_is_a_number1) == 1) {
      printf("%d", this_is_a_number1);
    } else {
        printf("Failed to read integer.\n");
    }

printf("You entered %d\n", this_is_a_number1);
printf("Please enter another number: \n");
if (scanf("%d", &this_is_a_number2) == 1) {
      printf("%d", this_is_a_number1);
    } else {
      printf("Failed to read integer.\n");
    }
printf("You entered %d\n", this_is_a_number2);
total = this_is_a_number1 + this_is_a_number2;/* add two numbers */
printf("total is %d\n", total);
return 0;
}
