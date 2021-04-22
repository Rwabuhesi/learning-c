#include <stdio.h>		//snprintf(), sscanf(), fprintf()
#include <string.h> //to access strcmp(), strncpy(), strlen()
#include <ctype.h>
#include <regex.h>	//access regcomp(), regexec(), alarm()
#include <time.h> //nanosleep()
#include <stdlib.h> //to access system()
#include <signal.h> //to access signal()

int menu1(void);
int menu2(void);
int menu3(void);
void menu4(void);

char ch; //hold characters in buffer
char pNumber[10]; //store user phone number
int	choice;		//store user's choice from menu
long int amount; //store amount to send;

int getChoice(int);		//get the user choice from menu
int charge(int); 	//calculate the service charges
int pause(long, long);	//pause the process

//function to clear the console
void clear_console(){
	system("cls||clear");	//'cls' for Windows systems, 'clear' fro LInux systems
}

//siganl handler function
void exit_sys(int sig){
	exit(0);
}

void exit_process(void){
	signal(SIGALRM, exit_sys); //handle alarm signal
	alarm(60); //init alarm signal after 60 seconds
}

int main(){
	char code[6];
	char mCode[6] = "*185#";

	printf("\t\t\tPlese enter service code...");
	scanf("%s", code);
	clear_console();
	pause(1,0); //pause the process for 1 second
	if(strcmp(code, mCode) == 0){
		exit_process();//exit if user doesn't enter any thing after 60 seconds
		choice = getChoice(menu1());
		pause(1,0);
		switch (choice){
				case 1:
				clear_console();
				exit_process();//exit if user doesn't enter any thing after 60 seconds
				choice = getChoice(menu2());
				pause(1,0);
				switch (choice){
					case 1:
						clear_console();
						menu3();
						exit_process();//exit if user doesn't enter any thing after 60 seconds
						scanf("%s", pNumber);
						// pause(1,0);
						regex_t re;
						regcomp(&re, "[a-zA-Z]", 0);  //pattern of alphabetical letter

						//when uses give an alphabetic or alphanumeric input
						while(regexec(&re, pNumber, 0, NULL, 0) == 0){
							clear_console();
							printf("\t\t\tPleae enter correct mobile number\n");
							printf("\t\t\tEnter Mobile number\n");
							exit_process();
							scanf("%s", pNumber);
						}

						while(strlen(pNumber) != 10){
							clear_console();
							pause(1,0);
							printf("\t\t\tPlease Enter the correct mobile number\n");
							printf("\t\t\tEnter Mobile number\n");
							exit_process();
							scanf("%s", pNumber);
						}

						char subNum[3];
						subNum[3] = '\0';
						strncpy(subNum, pNumber, 3); //create a sub-string of contact number

						regex_t re1, re2;

						regcomp(&re1, "070", 0);
						regcomp(&re2, "075", 0);

						while(regexec(&re1, subNum, 0, NULL, 0) == 1 && regexec(&re2, subNum, 0, NULL, 0) == 1){
							pause(1, 0);
							printf("\t\t\tPlease enter the correect number and try again\n");
							printf("\t\t\tNumbers should be in the form 070xxx or 075xxx\n");
							exit_process();
							scanf("%s", pNumber);
							strncpy(subNum, pNumber, 3);
							regexec(&re, subNum, 0, NULL, 0);
							regexec(&re2, subNum, 0, NULL, 0);
						}
						pause(1,0);
						clear_console();
						menu4();
						char str_amt[15]; //hold the amount as a string
						exit_process();
						scanf("%s", str_amt); //

						while(regexec(&re, str_amt, 0, NULL, 0) == 0){
							pause(1,0);
							printf("\t\t\tPlease enter the valid amount and try again\n");
							printf("\t\t\tEnter Amount\n");
							exit_process();
							scanf("%s", str_amt);
						}

						sscanf(str_amt, "%ld", &amount); //get amount as an integer

						while(amount < 500){
							pause(1,0);
							printf("\t\t\tDear Customer, transaction amount must\n\t\t\tbe more than UGX 500. Please try again\n\t\t\twith greater amount\n\t\t\tEnter Amount.\n");
							exit_process();//exit if user doesn't enter any thing after 60 seconds
							scanf("%s", str_amt);
							sscanf(str_amt, "%ld", &amount);
							pause(1,0);
						}

						char pin[4];
						char userPin[5] = {'8', '9', '8', '7', '\0'};

						float tax = amount*0.005;
						int charges = charge(amount);
						clear_console();
						pause(1,0);
						printf("\t\t\tSend UGX %ld to %s.\n\t\t\tCharge UGX %d.\n\t\t\tConfirm with your PIN\n", amount, pNumber, charges);
						exit_process();//exit if user doesn't enter any thing after 60 seconds
						scanf("%s", pin);

						while((strcmp(pin, userPin)) != 0){
							clear_console();
							pause(1, 0);
							printf("\t\t\tThe PIN you have entered is incorrect.\n\t\t\tPlease enter correct PIN.\n");
							exit_process();//exit if user doesn't enter any thing after 60 seconds
							scanf("%s", pin);
						}

						pause(2,0);
						printf("\t\t\tOperation Successful\n");
						printf("\t\t\tYou have sent %ld to %s and charged %d.\n\t\t\tTax: %.0f\n", amount, pNumber, charges, tax);

						FILE *file;
						file = fopen("transactionLog.txt", "a+");
						fprintf(file, "Number\t\tamount\t\tDate\t\tTime\n");

						time_t t = time(NULL);
						struct tm tm = *localtime(&t);

						fprintf(file, "%10s\t%10ld\t%d-%d-%d\t%2d:%2d:%d\n", pNumber, amount, (tm.tm_year + 1900), (tm.tm_mon + 1), tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

						// }else{
						// 		printf("\t\t\tEnter the correct mobile number\n");
						// }
						break;
					default:
						clear_console();
						printf("\t\t\tExternal application down\n");
						break;
					}
			break;
		default:
			clear_console();
			printf("\t\t\tExternal application down\n");
			break;
		}

	}else{
		printf("\t\t\tConnection problem or invalid MMI code\n");

	}
}

int menu1(void){
	// int
	printf("\t\t\t1.Send money\n");
	printf("\t\t\t2.Airtime/Bundles\n");
	printf("\t\t\t3.Withdraw cash\n");
	printf("\t\t\t4.Pay Bill\n");
	printf("\t\t\t5.Payments\n");
	printf("\t\t\t6.School fees\n");
	printf("\t\t\t7.Fincaial Services\n");
	printf("\t\t\t8.Wewole\n");
	printf("\t\t\t9.AirtelMoney Pay\n");
	printf("\t\t\t10.My Account\n");
	printf("\t\t\t11.Loans and Savings\n");

	return 11;
}
int menu2(void){
 	printf("\t\t\tSend Money\n");
 	printf("\t\t\t1.Airtel and other number\n");
 	printf("\t\t\t2.MTN number\n");
 	printf("\t\t\t3.UTL number\n");
 	printf("\t\t\t4.International Transfer\n");
 	printf("\t\t\t0.Back 00.Main Menu\n");

	return 4;
 }

int menu3(void){
	  printf("\t\t\tEnter Mobile Number\n");
	  printf("\t\t\t0.Back 00.Main Menu\n");

 }

void menu4(void){
	 printf("\t\t\tEnter Amount\n");
	 printf("\t\t\t0.Back 00.Main Menu\n");
 }

int getChoice(int m){
	if(scanf("%d", &choice) != 1){
			pause(1,0);
			printf("\t\t\tInvalid Option Selected\n");
			exit(0);
	}else{
		while(choice < 1 || choice > m){ //choice is out of range
			// clear_console();
			pause(1,0);
			printf("\t\t\tInvalid input. Please retry\n");
			scanf("%d", &choice);
			while((ch = getchar()) != '\n');  //ignore non-integer
		}
	}
	return choice;
}

int charge(int amount){
	int chg;
	if(amount >= 500 && amount <= 5000){
		chg = 100;
	}else if(amount >= 5001 && amount <= 60000){
		chg = 500;
	}else if(amount >= 60001 && amount <= 7000000){
		chg = 1000;
	}

	return chg;
}

int pause(long s, long ns){
	struct timespec tim, tim2;
	tim.tv_sec = s;
	tim.tv_nsec = ns;
	printf("\t\t\tUSSD code running...\n");
	nanosleep(&tim, &tim2);

}
