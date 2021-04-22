/* Write a program that accepts three values 
*from the user, selects the biggest 
*and computes it's square root.
*SOURCES: Class notes,  C Primer Plus 5th Edition by Prata */
#include <stdio.h>
#include <math.h> //to access sqrt()
int main(void)
{
    double square_root;
    float biggest_value = 0, i, value;
    int counter;
    char ch;	//hold non-interger input
    
    //get a value from the user
    puts("lets find the square root \nof the biggest value you enter");
    puts("Please enter first number");
    for(i = 0; i < 3; i++){
    
		while(scanf("%f", &value) != 1){	//if user enters non-integer
		    while((ch = getchar()) != '\n'){
		        putchar(ch);	//discard non-inter out
		    }
		    printf(" is not a nmber\n enter a number\n");
		}
		puts("Enter another value");
		
		if(value > biggest_value){
		    biggest_value = value;
		}
    }
    square_root = sqrt((double)biggest_value);
    printf("The square root of the biggest value %.2f is %.3f\n", biggest_value, square_root);
    
}
    
