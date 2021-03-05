#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#define DOWN 80
#define UP 72
#define RIGHT 77
#define LEFT 75

const int snakes_LENGTH = 52, snakes_HEIGHT = 22;

bool snakes_gameover;

char snakes_map[105][105];

int snakes_currSize, snakes_fruitRow, snakes_fruitCol, snakes_Score, snakes_Move;

double snakes_delaySec;

struct snakes_body{
	int row;
	int col;
};

struct snakes_score{
	char name[255];
	int score;
	struct snakes_score *next;
}*snakes_headScore = NULL, *snakes_tailScore = NULL;

void snakes_push(char *name, int score){
	struct snakes_score *tempSnake = (struct snakes_score*)malloc(sizeof(snakes_score));
	strcpy(tempSnake->name, name);
	tempSnake->score = score;
	tempSnake->next = NULL;
	if(snakes_headScore == NULL){
		snakes_headScore = snakes_tailScore = tempSnake;
	}
	else if(score>snakes_headScore->score){
		tempSnake -> next = snakes_headScore;
		snakes_headScore = tempSnake;
	}
	else if(score<snakes_tailScore->score){
		snakes_tailScore -> next = tempSnake;
		snakes_tailScore = tempSnake;
		snakes_tailScore -> next = NULL;
	}
	else{
		snakes_score *currScore = snakes_headScore;
		while(currScore->next != NULL && currScore->next->score > score){
			currScore = currScore->next;
		}
		tempSnake->next = currScore->next;
		currScore->next = tempSnake;
	}
}

void snakes_popHead(){
	if(!snakes_headScore){
		return;
	}
	else if(snakes_headScore == snakes_tailScore){
		snakes_headScore = snakes_tailScore = NULL;
	}
	else{
		struct snakes_score *currScore = snakes_headScore;
		snakes_headScore = currScore->next;
		free(currScore);	
	}
}

void snakes_popAll(){
	while(snakes_headScore){
		snakes_popHead();
	}
}

void snakes_setCursor(int x, int y) {
	COORD cursorPosition;
	cursorPosition.X = x;
	cursorPosition.Y = y;	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void snakes_setup(struct snakes_body *snakes){
	FILE *fmap = fopen(".\\Snakes\\SnakeMap.txt", "r");
	int index = 0;
	while(fscanf(fmap, "%[^\n]\n", snakes_map[index])!=EOF){
		index++;
	}
	fclose(fmap);
	snakes_currSize = 0;
	snakes[0].row = 11;
	snakes[0].col = 26;
	int fruitFlag = 1;
	do{
		fruitFlag = 1;
		srand(time(0));
		snakes_fruitRow = rand()%snakes_HEIGHT;
		srand(time(0));
		snakes_fruitCol = rand()%snakes_LENGTH;
		if(snakes_fruitRow<=0 || snakes_fruitRow>=snakes_HEIGHT || snakes_fruitCol<=0 || snakes_fruitCol>=snakes_LENGTH){
			fruitFlag = 0;
		}
		else if(snakes_fruitRow == snakes[0].row && snakes_fruitCol == snakes[0].col){
			fruitFlag = 0;
		}
	}while(fruitFlag == 0);
	snakes_gameover = false;
	snakes_Score = 0;
	snakes_delaySec = 2.5;
}

void snakes_draw(struct snakes_body *snakes){
	snakes_setCursor(0,0);
	//printf("\e[?25l");
	for(int i=0;i<=snakes_HEIGHT;++i){
		for(int j=0;j<=snakes_LENGTH; ++j){
			int snakeFlag = 0;
			for(int k=1;k<=snakes_currSize;++k){
				if(snakes[k].row == i && snakes[k].col == j){
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    				CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    				WORD saved_attributes;
				    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    				saved_attributes = consoleInfo.wAttributes;
					SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);
					printf("o");
					SetConsoleTextAttribute(hConsole,saved_attributes);
					snakeFlag = 1;
					break;
				}
			}
			if(snakeFlag==0){
				if(snakes[0].row == i && snakes[0].col == j){
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    				CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    				WORD saved_attributes;
				    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    				saved_attributes = consoleInfo.wAttributes;
					SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);
					printf("O");
					SetConsoleTextAttribute(hConsole,saved_attributes);
				}
				else{
					if(snakes_fruitRow == i && snakes_fruitCol==j){
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    					CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    					WORD saved_attributes;
				    	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    					saved_attributes = consoleInfo.wAttributes;
						SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
						printf("@");
						SetConsoleTextAttribute(hConsole,saved_attributes);
					}
					else{
						if(snakes_map[i][j]=='#'){
							HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    						CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    						WORD saved_attributes;
				    		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    						saved_attributes = consoleInfo.wAttributes;
							SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE);
							printf("%c", 219);
							SetConsoleTextAttribute(hConsole,saved_attributes);
						}
						else printf("%c", snakes_map[i][j]);
					}
				}
			}
		}
		printf("\n");
	}
	printf(" Score: %d\n", snakes_Score);
}

void snakes_input(struct snakes_body *snakes){
	if(_kbhit()){
		switch(_getch()){
			case UP:
				snakes_Move = 1; // up
				break;
			case DOWN:
				snakes_Move = 2; // down
				break;
			case LEFT:
				snakes_Move = 3; // left
				break;
			case RIGHT:
				snakes_Move = 4; // right
				break;
		}
	}
}

void snakes_logic(struct snakes_body *snakes){
	for(int i = snakes_currSize;i>0;--i){
		snakes[i].row = snakes[i-1].row;
		snakes[i].col = snakes[i-1].col;
	}
	switch(snakes_Move){
		case 1:
			snakes[0].row--;
			break;
		case 2:
			snakes[0].row++;
			break;
		case 3:
			snakes[0].col--;
			break;
		case 4:
			snakes[0].col++;
			break;
	}
	if(snakes[0].row < 1 || snakes[0].row >=22 || snakes[0].col<1 || snakes[0].col>=52){
		snakes_gameover = true;
	}
	for(int i=1;i<=snakes_currSize;++i){
		if(snakes[0].row == snakes[i].row && snakes[0].col == snakes[i].col){
			snakes_gameover = true;
			break;
		}
	}
	if(snakes[0].row == snakes_fruitRow && snakes[0].col == snakes_fruitCol){
		snakes_Score+=100;
		snakes_currSize++;
		if(snakes_delaySec>0.5){
			snakes_delaySec-=0.1;
		}
		int locationFlag = 1;
		do{
			locationFlag = 1;
			srand(time(0));
			snakes_fruitRow = rand()%snakes_HEIGHT;
			srand(time(0));
			snakes_fruitCol = rand()%snakes_LENGTH;
			for(int i=0;i<=snakes_currSize;++i){
				if(snakes[i].row == snakes_fruitRow && snakes[i].col == snakes_fruitCol){
					locationFlag = 0;
					break;
				}
			}
		}while(locationFlag == 0);
	}
}

void snakes_delay(double numsec){
	clock_t snakes_clockStart = clock();
	while(clock()< snakes_clockStart+100*numsec);
}

void snakes_startgame(){
	system("cls");
	struct snakes_body snakes[1005];
	snakes_setup(snakes);
	while(!snakes_gameover){
		snakes_draw(snakes);
		snakes_input(snakes);
		snakes_logic(snakes);
		snakes_delay(snakes_delaySec);
	}
	char name[255];
	int endFlag = 1;
	do{
		system("cls");
		endFlag = 1;
		printf(" Enter your name: ");
		scanf("%[^\n]", name);
		getchar();
		int len = strlen(name);
		if(len<3 || len>50){
			endFlag = 0;
			printf(" Name length must be between 3 - 50 characters!");
			getchar();
		}
		else{
			struct snakes_score *tempScore = snakes_headScore;
			while(tempScore){
				if(strcmp(tempScore->name, name)==0){
					endFlag = 0;
					printf(" Name must be unique!");
					getchar();
					break;
				}
				tempScore = tempScore->next;
			}
		}
	}while(endFlag ==0);
	FILE *fscore = fopen(".\\Snakes\\SnakeLeaderboard.txt", "a");
	fprintf(fscore, "%s#%d\n", name, snakes_Score);
	fclose(fscore);
	printf("Press enter to continue...");
	getchar();
	return;
}

void snakes_htp(){
	system("cls");
	printf(" You are a Snake who likes to eat fruits. \n");
	printf(" Your objective is to eat as many fruits as you can, and grow as long as you can!\n");
	printf(" You can move using arrow key (up,down, left, right) to move around inside the map.\n");
	printf(" Be careful not to bump into the walls, or your own body!\n");
	printf(" Your Score will be stored in the leaderboard!\n\n");
	printf(" Press enter to continue..");
	getchar();
	return;
}

void snakes_leaderboard(){
	system("cls");
	FILE *fscore = fopen(".\\Snakes\\SnakeLeaderboard.txt", "r");
	char names[255];
	int scores;
	while(fscanf(fscore, "%[^#]#%d\n", names, &scores)!=EOF){
		snakes_push(names, scores);
	}
	fclose(fscore);
	printf(" Current Leaderboard:\n");
	struct snakes_score *tempScore = snakes_headScore;
	while(tempScore){
		printf(" %-50s - %d \n", tempScore->name, tempScore->score);
		tempScore = tempScore->next;
	}
	snakes_popAll();
	printf("Press enter to continue..");
	getchar();
	return;
}

void snakes_game(){
	char snakes_choice;
	do{
		do{
			system("cls");
			printf("\t\t\t\t __             _             \n");
			printf("\t\t\t\t/ _\\_ __   __ _| | _____  ___ \n");
			printf("\t\t\t\t\\ \\| '_ \\ / _` | |/ / _ \\/ __|\n");
			printf("\t\t\t\t_\\ \\ | | | (_| |   <  __/\\__ \\\n");
			printf("\t\t\t\t\\__/_| |_|\\__,_|_|\\_\\___||___/\n\n"); 
			printf("\t\t	   /^\\/^\\\n");
			printf("\t\t         _|_O|__O|\n");
			printf("\t\t\\/     /~     \\_/ \\\n");
			printf("\t\t \\____|__________/  \\\n");
			printf("\t\t        \\_______      \\\n");
			printf("\t\t                `\\     \\                 \\\n");
			printf("\t\t                  |     |                  \\\n");
			printf("\t\t                 /      /                    \\\n");
			printf("\t\t                /     /                       \\\\\n");
			printf("\t\t              /      /                         \\ \\\n");
			printf("\t\t             /     /                            \\  \\\n");
			printf("\t\t           /     /             _----_            \\   \\\n");
			printf("\t\t          /     /           _-~      ~-_         |   |\n");
			printf("\t\t         (      (        _-~    _--_    ~-_     _/   |\n");
			printf("\t\t          \\      ~-____-~    _-~    ~-_    ~-_-~    /\n");
			printf("\t\t            ~-_           _-~          ~-_       _-~\n");
			printf("\t\t               ~--______-~                ~-___-~     \n\n");             
			printf("\t\t\t\t\t1. Play\n");
        	printf("\t\t\t\t\t2. How to Play\n");
        	printf("\t\t\t\t\t3. Leaderboard\n");
        	printf("\t\t\t\t\t4. Exit Game\n");
        	printf("\t\t\t\t\t>> ");
        	snakes_choice = getchar();
        	getchar();
		}while(snakes_choice-'0'<1 || snakes_choice-'0'>4);
		switch(snakes_choice-'0'){
			case 1:
				snakes_startgame();
				break;
			case 2:
				snakes_htp();
				break;
			case 3:
				snakes_leaderboard();
				break;
			case 4:
				break;
		}
	}while(snakes_choice-'0'!=4);
	return;
}
