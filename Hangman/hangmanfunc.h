#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
// Function Declaration
void hangman_strike1();
void hangman_strike2();
void hangman_strike3();
void hangman_strike4();
void hangman_strike5();
void hangman_strike6();
void hangman_strike7();
void hangman_logo ();
void hangman_hanged();
void hangman_loseMenu();
void hangman_winMenu();
void hangman_instructions();

int hangman_counter = 0;
int hangman_wordcounter = 0;
int hangman_test(char c, char *kata, char *tanya){
    int len = strlen(kata);
    for(int i = 0; i < len; i++){
       	if(c == kata[i]){
            tanya[i] = c;
    	}
	}
	//indikator kesalahan
	int lengthafter = len - hangman_wordcounter;
	int blankcounter = 0;
	hangman_wordcounter = 0;
	for(int b = 0; b < len; b++){
		if(tanya[b] == '*')blankcounter++;
	}
	for(int c = 0; c < len; c++){
		if(tanya[c] >= 'a' && tanya[c] <= 'z')hangman_wordcounter++;
	}
	if(blankcounter == lengthafter)hangman_counter++;
	if(hangman_counter == 1)hangman_strike1();
	else if(hangman_counter == 2)hangman_strike2();
	else if(hangman_counter == 3)hangman_strike3();
	else if(hangman_counter == 4)hangman_strike4();
	else if(hangman_counter == 5)hangman_strike5();
	else if(hangman_counter == 6)hangman_strike6();
	else if(hangman_counter == 7)hangman_strike7();
	printf("\n");
	for(int a = 0; a < len; a++){
		printf("%c", tanya[a]);
	}	
	printf("\n");
    return 1;
}

int hangman_checkwin(char*guess, char*answer){
	int flag = 1;
	int panjang = strlen(answer);
	for(int x = 0; x < panjang; x++){
		if(guess[x] != answer[x]) flag = 0;
	}
	if(flag == 1) return 1;
	else return -1;
}
void hangman_cont(){
	printf("\t\tPress Enter to Continue!");
	getchar();
	system("cls");
}
void hangman_startgame(){
	system("cls");
	int status;
	int victory = 0;
	int loss =0;
	int choice_flag = 1;
	//start game
	while(choice_flag==1){
		hangman_counter=0;
		hangman_hanged();
		//random question
		srand ( time(NULL));
   		int random;
   		random=(rand() % 12 );
  		char str[60][255];
  		FILE *fp = fopen(".\\Hangman\\HangmanAnswer.txt", "r");
		for(int i = 0; i < 60; i++) {
  	       	fscanf(fp, "%[^\n]\n", str[i]);
  		}
  		fclose(fp);
  		int len1 = strlen(str[random]);
		char answer[len1+1];
		char clue[225];
		strcpy(answer, str[random]);
		strcpy(clue, str[random+12]);
		int length = strlen(answer);
		//start guessing
		char guess[100];
		for(int i = 0; i < length; i++){
			guess[i]='*';
		}
		for(int i = 0; i < length; i++){
			printf("%c", guess[i]);
		}
		printf("\n");
		char letter;
		int win, len=1;
      	char input;
		do{
			printf("*Hint :  %s\n",clue);
			letter = getch();
			hangman_test(letter, answer, guess);
			win = hangman_checkwin(guess, answer);
		}while(win == -1 && hangman_counter < 8);
		//if win or lose
		if(win == 1 && hangman_counter < 8){
			victory ++;
			system("cls");
			hangman_winMenu();
			printf("\n\nWIN = %d\n", victory);
			printf("LOSS = %d\n\n", loss);
			getchar();
			printf("Do you want to continue game? [Y / N]: ");
        	scanf("%c", &input);
        	getchar();
           	if (input == 'Y' || input == 'y'){
           		choice_flag=1;
				system ("cls");
           	}
			else {
				choice_flag=0;
           		break;
            }
		}
		if(hangman_counter == 8){
			loss ++;
			system("cls");
			hangman_loseMenu();
			printf("\n\nWIN = %d\n", victory);
			printf("LOSS = %d\n\n", loss);
			getchar();
			printf("Do you want to try again? [Y / N]: ");
         	scanf("%c", &input);
         	getchar();
            if (input == 'Y' || input == 'y'){
            	choice_flag=1;
				system ("cls");
            }
			else {
				choice_flag=0;
            	break;
            }
		}
	}
	printf("\nNumber of Victories: %d\n", victory);
	printf("Number of Losses: %d\n", loss);
	getchar();
	hangman_cont();
	return;
}
void hangman_game(){
	char hangman_menu ;
	do{
		do{
			system("cls");
			hangman_logo();
			printf("\n");
			printf("\t\t\t\t\t\t\t1. Start Game\n");
			printf("\t\t\t\t\t\t\t2. Instructions\n");
			printf("\t\t\t\t\t\t\t3. Exit\n");
			printf("\t\t\t\t\t\t\t>> ");
			hangman_menu=getch();
			printf("%c\n", hangman_menu);
		}while(hangman_menu-'0'<1 || hangman_menu-'0'>3);
		switch(hangman_menu-'0'){
			case 1:
				hangman_startgame();
				break;
			case 2:
				hangman_instructions();
				break;
			case 3:
				break;
		}
	}while(hangman_menu-'0'!=3);
	return;
}
	
void hangman_instructions(){
	system("cls");
    printf("\n\t\t   ______                    \t\t\t     INSTRUCTIONS\n");
    printf("\t\t_|      |_____              HOW TO PLAY: \n");
	printf("\t\t|              |             1. The Player will think about the phrase/word for each letter of each word.\n");
    printf("\t\t|_________   _/              2. Player must guess a letter from a to z (lowercase) and type the letter\n");
    printf("\t\t|  |      | |                in guess column.\n");
    printf("\t\t|  |      | |                3. If that letter is in the word, the letter will appear in the word and if the letter\n");
    printf("\t\t|  |     /   \\               isn't in the word the body part will appears in the gallows.\n");
    printf("\t\t|  |    |     |              4. Player will continue guessing letters until they can solve the word\n");
    printf("\t\t|  |     \\___/               or all the body part appears in the gallows. \n\n");
    printf("\t\t|  |                         HOW TO WIN: \n");
    printf("\t\t|  |                         The Player wins if they guess the word before the person is hung.\n\n");
    printf("\t\t|  |                         WARNING!!\n");
    printf("\t\t|  |________                 YOU CAN ONLY PLAY THIS GAME 5 TIMES AT MAXIMUM\n");
    printf("\t\t|            \\______         (YOU CAN QUIT GAME EVERYTIME YOU FINISHES A GAME)\n");
    printf("\t\t|                   |__      THE ACCUMULATED POINTS WILL BE SHOWN AFTER YOU FINISHED THE GAME\n");
    printf("\t\t|______________________|     \n");
    getchar();
    hangman_cont();
	return;
   }
   
void hangman_strike1(){
	puts("YOU HAVE 7 GUESSES LEFT!");
	puts ("");
	puts ("");
	puts ("");
	puts ("");
	puts ("");
	puts ("");
	puts ("");
	printf("                               --------- \n");
}

void hangman_strike2(){
	printf("YOU HAVE 6 GUESSES LEFT!");
	printf("\n");
	printf("                               | \n");
	printf("                               | \n");
	printf("                               | \n");
	printf("                               | \n");
	printf("                               | \n");
	printf("                               | \n");
	printf("                              --------- \n");
}

void hangman_strike3(){
	printf("YOU HAVE 5 GUESSES LEFT!");
	printf("      ------\n");
	printf("                               | \n");
	printf("                               | \n");
	printf("                               | \n");
	printf("                               | \n");
	printf("                               | \n");
	printf("                               | \n");
	printf("                              --------- \n");
}

void hangman_strike4(){
	printf("YOU HAVE 4 GUESSES LEFT!");
	printf("      ------\n");
	printf("                               |   | \n");
	printf("                               |   \n");
	printf("                               |  \n");
	printf("                               |  \n");
	printf("                               |  \n");
	printf("                               | \n");
	printf("                              --------- \n");
}

void hangman_strike5(){
	printf("YOU HAVE 3 GUESSES LEFT!");
	printf("      ------\n");
	printf("                               |   | \n");
	printf("                               |   O \n");
	printf("                               |  \n");
	printf("                               |  \n");
	printf("                               |  \n");
	printf("                               | \n");		
	printf("                              --------- \n");
}

void hangman_strike6(){
	printf("YOU HAVE 2 GUESSES LEFT!");
	printf("      ------\n");
	printf("                               |   | \n");
	printf("                               |   O \n");
	printf("                               |  /|\\ \n");
	printf("                               |    \n");
	printf("                               |  \n");
	printf("                               | \n");
	printf("                              --------- \n");
}
void hangman_strike7(){
	printf("YOU HAVE 1 GUESS LEFT!");
	printf("        ------\n");
	printf("                               |   | \n");
	printf("                               |   O \n");
	printf("                               |  /|\\ \n");
	printf("                               |   | \n");
	printf("                               | \n");
	printf("                               | \n");
	printf("                              --------- \n");
}

void hangman_hanged(){
	printf("                              ------\n");
	printf("                               |   | \n");
	printf("                               |   O \n");
	printf("                               |  /|\\ \n");
	printf("                               |   | \n");
	printf("                               |  / \\ \n");
	printf("                               | \n");
	printf("                              --------- \n");
}

void hangman_logo(){
    printf("\t\t##                                                                                           ###   \n");
	printf("\t\t####                                                                                         ##### \n");
    printf("\t\t####    ##                                                                                   ##### \n");
    printf("\t\t####    ### #                             #########                                    ##    ####  \n");
    printf("\t\t###     ####                     ####  #####    ####    ##       ####               #####   #####  \n");
    printf("\t\t###     ####     ###      ####   ####  #####     ####  ####      ####     ####      #####   ####   \n");
	printf("\t\t###     # #     #####     ####   ####  ####       ##   ####     #####   ######      #####   ####   \n");
	printf("\t\t#####  #####   #######   ######  #### #####            #####   ######   #######    #######  ####   \n");
    printf("\t\t###########    ##  ###   ######  #### ####            ######   ######   ### ####   #######  ####   \n");
    printf("\t\t############# ###   ##   ####### #### #### ########## ######  #######  ###   ###   #######  ####   \n");
    printf("\t\t####    ####  ###  ####  #######  ### ####  ######### ### ### ### ###  ####  ###   ######## ####   \n");
    printf("\t\t####    ####  #########  ###  #############     ######### ######  ###  ##########  #############   \n");
    printf("\t\t####    ###  ### ## ###  ###  ####### #######  #####  ###  ####  #### #### ######  ###  ########   \n");
    printf("\t\t## #   ########      ### ###  #######  ###########    ##   ###   #### ###      ### ###   #######   \n");
    printf("\t\t###     ###          #######   ######                      #    #### ###         ####   #######    \n");
	printf("\t\t##     ####          ###           ##                            # #####           ###   #######   \n");
    printf("\t\t##      ##                                                                         ##              \n");
    printf("\t\t#                                                                                                  \n");
}

void hangman_loseMenu() {
	printf("\t\t  ______    _______              _______      ________               ________   ______     \n");
	printf("\t\t |         |   _   |  |\\    /|  |            |        |  \\        / |          |      |    \n");
	printf("\t\t |         |  /_\\  |  | \\  / |  |            |        |   \\      /  |          |______|     \n");
	printf("\t\t |   ____  |  ___  |  |  \\/  |  |-------     |        |    \\    /   |--------  | \\         \n");
	printf("\t\t |      |  | |   | |  |      |  |            |        |     \\  /    |          |   \\       \n");
	printf("\t\t |______|  |_|   |_|  |      |  |_______     |________|      \\/     |________  |     \\     \n\n");
}

void hangman_winMenu() {
	printf("\t\t\\\  /   _______              \\\                /  _  |\\    | \n");
	printf("\t\t \\\/   |       |  |      |    \\\      /\\\      /  | | | \\   | \n");
	printf("\t\t ||   |       |  |      |     \\\    /  \\\    /   | | |  \\  | \n");
	printf("\t\t ||   |       |  |      |      \\\  /    \\\  /    | | |   \\ | \n");
	printf("\t\t ||   |_______|  |______|       \\\/      \\\/     |_| |    \\| \n\n");
}
