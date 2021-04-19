#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

// VARIABLES INITIALIZATION
struct monsterMaze_frag {
	int row;
	int col;
	bool valid = true;
}monsterMaze_fragment[5];

int monsterMaze_lapse = 0, monsterMaze_move;
int monsterMaze_currFragments=0;
int monsterMaze_index=0;

int monsterMaze_playerRow = 1, monsterMaze_playerCol = 1;
bool monsterMaze_alive = true, monsterMaze_win = false;

char monsterMaze_map[100][100];

int monsterMaze_enemyRow[3], monsterMaze_enemyCol[3];

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------

// BFS PREPARATION
int monsterMaze_currIndex[3] = {0 }, monsterMaze_rowChoice = 1, monsterMaze_colChoice = 1;
bool monsterMaze_visitedForQueue[100][100] = {false};

struct monsterMaze_enemy {
	int row;
	int col;
} monsterMaze_queue[3][1000];

int monsterMaze_prevRow[3][1000][1000], monsterMaze_prevCol[3][1000][1000];

void monsterMaze_clearVisited(){
	for(int i=0;i<100;i++){
		for(int j=0;j<100;j++){
			monsterMaze_visitedForQueue[i][j] = false;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// BFS IMPLEMENTATION
void monsterMaze_createQueue(int monsterMaze_enemyIndex){
    monsterMaze_currIndex[monsterMaze_enemyIndex] = 0;
	int monsterMaze_front = 0, monsterMaze_length=1;
	monsterMaze_queue[monsterMaze_enemyIndex][monsterMaze_currIndex[monsterMaze_enemyIndex]].row = monsterMaze_enemyRow[monsterMaze_enemyIndex];
	monsterMaze_queue[monsterMaze_enemyIndex][monsterMaze_currIndex[monsterMaze_enemyIndex]].col = monsterMaze_enemyCol[monsterMaze_enemyIndex];
	monsterMaze_prevRow[monsterMaze_enemyIndex][monsterMaze_queue[monsterMaze_enemyIndex][monsterMaze_currIndex[monsterMaze_enemyIndex]].row][monsterMaze_queue[monsterMaze_enemyIndex][monsterMaze_currIndex[monsterMaze_enemyIndex]].col] = monsterMaze_enemyRow[monsterMaze_enemyIndex];
    monsterMaze_prevCol[monsterMaze_enemyIndex][monsterMaze_queue[monsterMaze_enemyIndex][monsterMaze_currIndex[monsterMaze_enemyIndex]].row][monsterMaze_queue[monsterMaze_enemyIndex][monsterMaze_currIndex[monsterMaze_enemyIndex]].col] = monsterMaze_enemyCol[monsterMaze_enemyIndex];
    int r1[4] = {1, 0, -1, 0}, c1[4] = {0, 1, 0, -1};
    for(int j=monsterMaze_front;j<=monsterMaze_length;j++){
        for(int i=0;i<4;i++){
            if(monsterMaze_map[monsterMaze_queue[monsterMaze_enemyIndex][j].row+r1[i]][monsterMaze_queue[monsterMaze_enemyIndex][j].col+c1[i]]==' ' && monsterMaze_visitedForQueue[monsterMaze_queue[monsterMaze_enemyIndex][j].row+r1[i]][monsterMaze_queue[monsterMaze_enemyIndex][j].col+c1[i]] == false){
                monsterMaze_length++;
				monsterMaze_currIndex[monsterMaze_enemyIndex]++;
                monsterMaze_queue[monsterMaze_enemyIndex][monsterMaze_currIndex[monsterMaze_enemyIndex]].row = monsterMaze_queue[monsterMaze_enemyIndex][j].row+r1[i];
            	monsterMaze_queue[monsterMaze_enemyIndex][monsterMaze_currIndex[monsterMaze_enemyIndex]].col = monsterMaze_queue[monsterMaze_enemyIndex][j].col+c1[i];
                monsterMaze_visitedForQueue[monsterMaze_queue[monsterMaze_enemyIndex][j].row+r1[i]][monsterMaze_queue[monsterMaze_enemyIndex][j].col+c1[i]] = true;
                monsterMaze_prevRow[monsterMaze_enemyIndex][monsterMaze_queue[monsterMaze_enemyIndex][j].row+r1[i]][monsterMaze_queue[monsterMaze_enemyIndex][j].col+c1[i]] = monsterMaze_queue[monsterMaze_enemyIndex][j].row;
                monsterMaze_prevCol[monsterMaze_enemyIndex][monsterMaze_queue[monsterMaze_enemyIndex][j].row+r1[i]][monsterMaze_queue[monsterMaze_enemyIndex][j].col+c1[i]] = monsterMaze_queue[monsterMaze_enemyIndex][j].col;
            } 
        }
    }
    return;
}

// BACKTRACK PATH
void monsterMaze_choosePath(int monsterMaze_enemyIndex){
	int monsterMaze_currRow = monsterMaze_playerRow, monsterMaze_currCol = monsterMaze_playerCol, monsterMaze_rowNote=monsterMaze_playerRow, monsterMaze_colNote=monsterMaze_playerCol;
	while((monsterMaze_currRow!=monsterMaze_enemyRow[monsterMaze_enemyIndex]) || (monsterMaze_currCol !=monsterMaze_enemyCol[monsterMaze_enemyIndex])){
		int monsterMaze_nextRow = monsterMaze_prevRow[monsterMaze_enemyIndex][monsterMaze_currRow][monsterMaze_currCol];
		int monsterMaze_nextCol = monsterMaze_prevCol[monsterMaze_enemyIndex][monsterMaze_currRow][monsterMaze_currCol];
		monsterMaze_rowNote = monsterMaze_currRow;
		monsterMaze_colNote = monsterMaze_currCol;
		monsterMaze_currRow = monsterMaze_nextRow;
		monsterMaze_currCol = monsterMaze_nextCol;
	}	
	monsterMaze_rowChoice = monsterMaze_rowNote;
	monsterMaze_colChoice = monsterMaze_colNote;
	return;
}

// SET MOVEMENT
void monsterMaze_enemyMove(int monsterMaze_enemyIndex){
	monsterMaze_choosePath(monsterMaze_enemyIndex);
	monsterMaze_enemyRow[monsterMaze_enemyIndex] =  monsterMaze_rowChoice;
	monsterMaze_enemyCol[monsterMaze_enemyIndex] =  monsterMaze_colChoice;
	return;
}

// GAME SETUP
void monsterMaze_setup(){
	monsterMaze_index=0;
	FILE *fmap = fopen(".\\PRE TRAINING\\Monster Maze\\MonsterMazeMap.txt", "r");
	while(fscanf(fmap, "%[^\n]\n", monsterMaze_map[monsterMaze_index])!=EOF){
		monsterMaze_index++;
	}
	monsterMaze_alive = true;
	monsterMaze_win = false;
	monsterMaze_currFragments = 0;
	monsterMaze_playerRow = 1;
	monsterMaze_playerCol = 1;
	monsterMaze_enemyRow[0] = 1;
	monsterMaze_enemyCol[0] = 72;
	monsterMaze_enemyRow[1] = 20;
	monsterMaze_enemyCol[1] = 1;
	monsterMaze_enemyRow[2] = 20;
	monsterMaze_enemyCol[2] = 72;
	monsterMaze_createQueue(0);
	monsterMaze_clearVisited();
	monsterMaze_createQueue(1);
	monsterMaze_clearVisited();
	monsterMaze_createQueue(2);
	monsterMaze_clearVisited();
	for(int i=0;i<5;i++){
		int monsterMaze_flag = 1;
		do{
			monsterMaze_flag = 1;
			srand(time(0));
			monsterMaze_fragment[i].row = 1 + rand()%20;
			monsterMaze_fragment[i].col = 1 + rand()%72;
			if(monsterMaze_fragment[i].row== monsterMaze_playerRow && monsterMaze_fragment[i].col==monsterMaze_playerCol){
				monsterMaze_flag = 0;
			}
			for(int j=0;j<i;j++){
				if(monsterMaze_fragment[i].row==monsterMaze_fragment[j].row && monsterMaze_fragment[i].col==monsterMaze_fragment[j].col){
					monsterMaze_flag = 0;
					break;
				}
			}
			for(int k=0;k<3;k++){
				if(monsterMaze_fragment[i].row ==monsterMaze_enemyRow[k] && monsterMaze_fragment[i].col==monsterMaze_enemyCol[k]){
					monsterMaze_flag = 0;
					break;
				}
			}
			if(monsterMaze_map[monsterMaze_fragment[i].row][monsterMaze_fragment[i].col]!=' '){
				monsterMaze_flag = 0;
			}
		}while(monsterMaze_flag ==0);
	}
}

// BEAUTIFY :)
void monsterMaze_setCursor(int x, int y) {
	COORD cursorPosition;
	cursorPosition.X = x;
	cursorPosition.Y = y;	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

// PRINT MAP
void monsterMaze_printmap(){
	monsterMaze_setCursor(0,0);
	printf("\e[?25l");
	for(int i=0;i<monsterMaze_index;i++){
		for(int j=0;j<75;j++){
			if(i==monsterMaze_playerRow && j==monsterMaze_playerCol){
				printf("P");
			}
			else if(i==monsterMaze_enemyRow[0] && j==monsterMaze_enemyCol[0]){
				printf("E");
			}
			else if(i==monsterMaze_enemyRow[1] && j==monsterMaze_enemyCol[1]){
				printf("E");
			}
			else if(i==monsterMaze_enemyRow[2] && j==monsterMaze_enemyCol[2]){
				printf("E");
			}
			else if(monsterMaze_fragment[0].valid==true && i ==monsterMaze_fragment[0].row && j==monsterMaze_fragment[0].col){
				printf("*");
			}
			else if(monsterMaze_fragment[1].valid==true && i ==monsterMaze_fragment[1].row && j==monsterMaze_fragment[1].col){
				printf("*");
			}
			else if(monsterMaze_fragment[2].valid==true && i ==monsterMaze_fragment[2].row && j==monsterMaze_fragment[2].col){
				printf("*");
			}
			else if(monsterMaze_fragment[3].valid==true && i ==monsterMaze_fragment[3].row && j==monsterMaze_fragment[3].col){
				printf("*");
			}
			else if(monsterMaze_fragment[4].valid==true && i ==monsterMaze_fragment[4].row && j==monsterMaze_fragment[4].col){
				printf("*");
			}
			else if(i==15 && j==73 && monsterMaze_currFragments==5){
				printf(" ");
			}
			else printf("%c", monsterMaze_map[i][j]);
		}
		printf("\n");
	}
	printf("Key Fragments Collected = %d\n", monsterMaze_currFragments);
}

// ACCEPT KEY INPUT
void monsterMaze_input(){
	monsterMaze_move = 0;
	if(_kbhit()){
		switch(_getch()){
			case 'a':
				monsterMaze_move = 1; // left
				break;
			case 'A':
				monsterMaze_move = 1; // left
				break;
			case 'd':
				monsterMaze_move = 2; // right
				break;
			case 'D':
				monsterMaze_move = 2; // right
				break;
			case 'w':
				monsterMaze_move = 3; // up
				break;
			case 'W':
				monsterMaze_move = 3; // up
				break;
			case 's':
				monsterMaze_move = 4; // down
				break;
			case 'S':
				monsterMaze_move = 4; // down
				break;
		}
	}
}

// GAME LOGIC
void monsterMaze_logic(){
	switch(monsterMaze_move){
		case 1:
			if(monsterMaze_map[monsterMaze_playerRow][monsterMaze_playerCol-1]!='#'){
				monsterMaze_playerCol--;
			}
			break;
		case 2:
			if(monsterMaze_map[monsterMaze_playerRow][monsterMaze_playerCol+1]!='#'){
				monsterMaze_playerCol++;
			}
			break;
		case 3:
			if(monsterMaze_map[monsterMaze_playerRow-1][monsterMaze_playerCol]!='#'){
				monsterMaze_playerRow--;
			}
			break;
		case 4:
			if(monsterMaze_map[monsterMaze_playerRow+1][monsterMaze_playerCol]!='#'){
				monsterMaze_playerRow++;
			}
			break;
	}
	for(int i=0;i<3;i++){
		if(monsterMaze_playerRow == monsterMaze_enemyRow[i] && monsterMaze_playerCol==monsterMaze_enemyCol[i]){
			monsterMaze_alive = false;
			return;
		}
	}
	for(int i=0;i<5;i++){
		if(monsterMaze_fragment[i].valid==true && monsterMaze_playerRow == monsterMaze_fragment[i].row && monsterMaze_playerCol==monsterMaze_fragment[i].col){
			monsterMaze_fragment[i].valid=false;
			monsterMaze_currFragments++;
			break;
		}
	}
	if(monsterMaze_playerRow == 15 && monsterMaze_playerCol==73){
		monsterMaze_win=true;
	}
	monsterMaze_createQueue(0);
	monsterMaze_clearVisited();
	monsterMaze_createQueue(1);
	monsterMaze_clearVisited();
	monsterMaze_createQueue(2);
	monsterMaze_clearVisited();
}

// UTILITY FUNCTION
void monsterMaze_delay(double numsec){
	clock_t monsterMaze_clockStart = clock();
	while(clock()< monsterMaze_clockStart+100*numsec);
}

// GAME LOOP
void monsterMaze_startgame(){	
	char monsterMaze_difficulty = '0';
	do{
		monsterMaze_difficulty = '0';
		system("cls");
		printf(" Select difficulty\n");
		printf(" 1. Insane\n");
		printf(" 2. Hard\n");
		printf(" 3. Easy\n");
		printf(" >> ");
		monsterMaze_difficulty = getch();
		printf("%c\n", monsterMaze_difficulty);
	}while(monsterMaze_difficulty-'0'<1 || monsterMaze_difficulty-'0'>3);
	switch(monsterMaze_difficulty-'0'){
		case 1:
			monsterMaze_lapse = 1;
			break;
		case 2:
			monsterMaze_lapse = 2;
			break;
		case 3:
			monsterMaze_lapse = 3;
			break;
	}
	monsterMaze_setup();
	int monsterMaze_start = 1;
	monsterMaze_printmap();
	monsterMaze_input();
	monsterMaze_logic();
	while(monsterMaze_alive==true && monsterMaze_win==false){
		//system("cls");
		monsterMaze_printmap();
		monsterMaze_input();
		monsterMaze_logic();
		if(monsterMaze_start%monsterMaze_lapse==0){
			monsterMaze_enemyMove(0);
			monsterMaze_enemyMove(1);
			monsterMaze_enemyMove(2);
		}
		monsterMaze_delay(1);
		monsterMaze_start++;
		//break;
	}
	if(monsterMaze_win==true){
		system("cls");
		printf("           __   _____  _   _  __        _____ _   _\n");
	    printf("    __/\\__ \\ \\ / / _ \\| | | | \\ \\      / /_ _| \\ | | __/\\__\n");
		printf("    \\    /  \\ V / | | | | | |  \\ \\ /\\ / / | ||  \\| | \\    /\n");
   		printf("    /_  _\\   | || |_| | |_| |   \\ V  V /  | || |\\  | /_  _\\\n");
   		printf("      \\/     |_| \\___/ \\___/     \\_/\\_/  |___|_| \\_|   \\/\n\n\n");
	}
	else if(monsterMaze_alive == false){
		system("cls");
		printf("     __   __   _____  _   _   _     ___  ____  _____    __\n");
    	printf("     \\ \\  \\ \\ / / _ \\| | | | | |   / _ \\/ ___|| ____|  / /\n");
    	printf("      \\ \\  \\ V / | | | | | | | |  | | | \\___ \\|  _|   / /\n");
    	printf("      / /   | || |_| | |_| | | |__| |_| |___) | |___  \\ \\\n");
    	printf("     /_/    |_| \\___/ \\___/  |_____\\___/|____/|_____|  \\_\\\n\n\n");
	}
	printf("\t\tPress enter to continue...");
	getchar();
	return;
}

// HOW TO PLAY
void monsterMaze_htp(){
	system("cls");
	printf(" Welcome to Monster Maze,\n\n");
    printf("     You are now locked inside this maze by the evil wizard Ajax,\n\n");
    printf("     but there is no maze that has no end!\n");
    printf("     If you look carefully you could find the escape door symbolized by '|' on the map.\n\n");
    printf("     You should find 5 key fragments scattered around the maze in order to unlock that door and escape.\n");
    printf("     The fragments are symbolized by '*' on the map, to get it you should travel the maze carefully!\n\n");
    printf("     Use 'W' to move upwards, 'S' to move downwards, 'A' to move left and 'D' to move right.\n\n");
    printf("     After you gather all of the fragments the door should be automatically opened.\n");
    printf("     Be quick before the monsters of the maze catch up on you!\n\n");
    printf("     Press any key to continue . .");
    getch();
    return;
}

// DRIVER
void monsterMaze_game(){
	printf("\e[?25l");
	char monsterMaze_mainChoice='0';
	do{
		do{
			monsterMaze_mainChoice='0';
			system("cls");
			printf("\t\t    ___  ___                _             ___  ___   \n");           
			printf("\t\t    |  \\/  |               | |            |  \\/  |         \n");     
			printf("\t\t    | .  . | ___  _ __  ___| |_ ___ _ __  | .  . | __ _ _______ \n");
			printf("\t\t    | |\\/| |/ _ \\| '_ \\/ __| __/ _ \\ '__| | |\\/| |/ _` |_  / _ \\\n");
			printf("\t\t    | |  | | (_) | | | \\__ \\ ||  __/ |    | |  | | (_| |/ /  __/\n");
			printf("\t\t    \\_|  |_/\\___/|_| |_|___/\\__\\___|_|    \\_|  |_/\\__,_/___\\___|\n\n");
        	printf("\t\t\t\t\t1. Play\n");
        	printf("\t\t\t\t\t2. How to Play\n");
        	printf("\t\t\t\t\t3. Exit Game\n");
        	printf("\t\t\t\t\t>> ");
        	monsterMaze_mainChoice = getch();
        	printf("%c\n", monsterMaze_mainChoice);
		}while(monsterMaze_mainChoice-'0'<1 || monsterMaze_mainChoice-'0'>3);
		switch(monsterMaze_mainChoice-'0'){
			case 1:
				monsterMaze_startgame();
				break;
			case 2:
				monsterMaze_htp();
				break;
		}
	}while(monsterMaze_mainChoice-'0'!=3);
	return;
}
