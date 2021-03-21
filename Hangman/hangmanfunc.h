#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

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

struct hangman_score{
	char name[255];
	int win, loss;
	struct hangman_score *next;
}*hangman_headScore = NULL, *hangman_tailScore = NULL;

void hangman_push(char *name, int win, int loss){
	struct hangman_score *temp = (struct hangman_score*)malloc(sizeof(hangman_score));
	strcpy(temp->name, name);
	temp->win = win;
	temp->loss = loss;
	temp->next = NULL;
	if(hangman_headScore == NULL){
		hangman_headScore = hangman_tailScore = temp;
	}
	else if(win>hangman_headScore->win){
		temp-> next = hangman_headScore;
		hangman_headScore = temp;
	}
	else if(win<hangman_tailScore->win){
		hangman_tailScore -> next = temp;
		hangman_tailScore = temp;
		hangman_tailScore -> next = NULL;
	}
	else{
		hangman_score *currScore = hangman_headScore;
		while(currScore->next != NULL && currScore->next->win > win){
			currScore = currScore->next;
		}
		temp->next = currScore->next;
		currScore->next = temp;
	}
}

void hangman_popHead(){
	if(!hangman_headScore){
		return;
	}
	else if(hangman_headScore == hangman_tailScore){
		hangman_headScore = hangman_tailScore = NULL;
	}
	else{
		struct hangman_score *currScore = hangman_headScore;
		hangman_headScore = currScore->next;
		free(currScore);	
	}
}

void hangman_popAll(){
	while(hangman_headScore){
		hangman_popHead();
	}
}

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
	printf("\n ");
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
	printf("\t\t Press Enter to Continue!");
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
		printf(" ");
		for(int i = 0; i < length; i++){
			printf("%c", guess[i]);
		}
		printf("\n");
		char letter;
		int win, len=1;
      	char input;
		do{
			printf(" *Hint :  %s\n",clue);
			letter = getch();
			hangman_test(letter, answer, guess);
			win = hangman_checkwin(guess, answer);
		}while(win == -1 && hangman_counter < 8);
		//if win or lose
		if(win == 1 && hangman_counter < 8){
			victory ++;
			system("cls");
			hangman_winMenu();
			printf("\n\n WIN = %d\n", victory);
			printf(" LOSS = %d\n\n", loss);
			getchar();
			printf(" Do you want to continue game? [Y / N]: ");
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
			printf("\n\n WIN = %d\n", victory);
			printf(" LOSS = %d\n\n", loss);
			getchar();
			printf(" Do you want to try again? [Y / N]: ");
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
	printf("\n Number of Victories: %d\n", victory);
	printf(" Number of Losses: %d\n\n", loss);
	char choice[5];
	bool saveFlag = true;
	do{
		saveFlag = false;
		printf(" Do you want to save your streak?[Yes|No]\n");
		printf(" >> ");
		scanf("%s", choice);
		getchar();
		if(strcmpi(choice,"yes")==0 || strcmpi(choice,"no")==0){
			saveFlag = true;
		}
	}while(!saveFlag);
	if(strcmpi(choice,"yes")==0){
		char name[255];
		do{
			saveFlag = true;
			printf(" Please enter your name [3-25 characters]: ");
			scanf("%[^\n]", name);
			getchar();
			int len = strlen(name);
			if(len<3 || len>25){
				saveFlag=false;
			}
		}while(!saveFlag);
		FILE *fscore = fopen(".\\Hangman\\HangmanLeaderboard.txt","a");
		fprintf(fscore, "%s#%d#%d\n", name, victory, loss);
		fclose(fscore);
		printf(" Save completed!\n");
	}
	printf(" Press enter to continue...");
	getchar();
	return;
}

void hangman_leaderboard(){
	system("cls");
	FILE *fscore = fopen(".\\Hangman\\HangmanLeaderboard.txt", "r");
	char names[255];
	int win, loss;
	while(fscanf(fscore, "%[^#]#%d#%d\n", names, &win, &loss)!=EOF){
		hangman_push(names, win,loss);
	}
	fclose(fscore);
	if(!hangman_headScore){
		printf(" There is no data!\n");
	}
	else{
		printf(" Current Leaderboard:\n\n");
		struct hangman_score *tempScore = hangman_headScore;
		printf(" +---------------------------+-----+------+\n");
		printf(" | Name                      | Win | Loss |\n");
		printf(" +---------------------------+-----+------+\n");
		while(tempScore){
			printf(" | %-25s | %-3d | %-3d  |\n", tempScore->name, tempScore->win, tempScore->loss);
			printf(" +---------------------------+-----+------+\n");
			tempScore = tempScore->next;
		}
	}
	hangman_popAll();
	printf("Press enter to continue..");
	getchar();
	return;
}

void hangman_game(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const SMALL_RECT WinSize = {0,0,135,30};
    SetConsoleWindowInfo( hConsole, true, &WinSize);
	char hangman_menu ;
	do{
		do{
			system("cls");
			hangman_logo();
			printf("\n");
			printf("\t\t\t\t\t\t\t1. Start Game\n");
			printf("\t\t\t\t\t\t\t2. Instructions\n");
			printf("\t\t\t\t\t\t\t3. Leaderboard\n");
			printf("\t\t\t\t\t\t\t4. Exit\n");
			printf("\t\t\t\t\t\t\t>> ");
			hangman_menu=getch();
			printf("%c\n", hangman_menu);
		}while(hangman_menu-'0'<1 || hangman_menu-'0'>4);
		switch(hangman_menu-'0'){
			case 1:
				hangman_startgame();
				break;
			case 2:
				hangman_instructions();
				break;
			case 3:
				hangman_leaderboard();
				break;
		}
	}while(hangman_menu-'0'!=4);
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
	printf(" YOU HAVE 6 GUESSES LEFT!");
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
	printf(" YOU HAVE 5 GUESSES LEFT!");
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
	printf(" YOU HAVE 4 GUESSES LEFT!");
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
	printf(" YOU HAVE 3 GUESSES LEFT!");
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
	printf(" YOU HAVE 2 GUESSES LEFT!");
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
	printf(" YOU HAVE 1 GUESS LEFT!");
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
