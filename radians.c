#include <stdio.h>
float angle, radian;
const double PI = 3.14159;
char ch;

int main(){
	//Get an angle from the user
	puts("Please provide angle in degrees");
	while(scanf("%f", &angle) != 1){	//if user enters non-integer
		    while((ch = getchar()) != '\n'){
		        putchar(ch);	//discard non-inter out
		    }
		    printf(" is not a number\n Enter a numberic angle\n");
	}
	
	radian = (angle *PI)/180;	//compute angle in Radians
	printf("The angle %.2f degrees is %.3f radians\n", angle, radian);
	
	return 0;
}
