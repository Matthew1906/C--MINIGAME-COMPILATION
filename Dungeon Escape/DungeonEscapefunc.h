#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
char dungeonEscape_dungeonMap[100][100];
bool dungeonEscape_alive = true, dungeonEscape_win = false;
int dungeonEscape_playerRow, dungeonEscape_playerCol, dungeonEscape_playerMove;
int dungeonEscape_trap1Row, dungeonEscape_trap1Col, dungeonEscape_trap2Row, dungeonEscape_trap2Col;
int dungeonEscape_monster1Row, dungeonEscape_monster1Col, dungeonEscape_monster2Row, dungeonEscape_monster2Col;

void dungeonEscape_delay(double numsec){
	clock_t start = clock();
	while(clock()< start+100*numsec);
}

void dungeonEscape_setup(){
	dungeonEscape_alive = true;
	dungeonEscape_win = false;
	dungeonEscape_playerRow = 1, dungeonEscape_playerCol = 1;
	bool dungeonEscape_alive = true;
	dungeonEscape_trap1Row=0, dungeonEscape_trap1Col=0, dungeonEscape_trap2Row=0, dungeonEscape_trap2Col=0, dungeonEscape_monster1Row=0, dungeonEscape_monster1Col=0, dungeonEscape_monster2Row=0, dungeonEscape_monster2Col=0;
	do{
		srand(time(0));
		dungeonEscape_trap1Row = rand()%9;
		srand(time(0));
		dungeonEscape_trap1Col = rand()%17;
	}while(dungeonEscape_trap1Row==1 || dungeonEscape_trap1Col==1 || dungeonEscape_trap1Row==7 || dungeonEscape_trap1Col==14|| dungeonEscape_dungeonMap[dungeonEscape_trap1Row][dungeonEscape_trap1Col]=='#');
	do{
		srand(time(0));
		dungeonEscape_trap2Row = rand()%9;
		srand(time(0));
		dungeonEscape_trap2Col = rand()%17;
	}while(dungeonEscape_trap2Row==1 || dungeonEscape_trap2Row==7|| dungeonEscape_trap2Col==1 || dungeonEscape_trap2Col==14|| dungeonEscape_dungeonMap[dungeonEscape_trap2Row][dungeonEscape_trap2Col]=='#' || dungeonEscape_trap1Row==dungeonEscape_trap2Row || dungeonEscape_trap1Col==dungeonEscape_trap2Col);
	do{
		srand(time(0));
		dungeonEscape_monster1Row = rand()%9;
		srand(time(0));
		dungeonEscape_monster1Col = rand()%17;
	}while(dungeonEscape_monster1Row==1 || dungeonEscape_monster1Col==1 || dungeonEscape_dungeonMap[dungeonEscape_monster1Row][dungeonEscape_monster1Col]=='#'|| dungeonEscape_dungeonMap[dungeonEscape_monster1Row][dungeonEscape_monster1Col]=='*'  || dungeonEscape_monster1Row==dungeonEscape_trap2Row || dungeonEscape_monster1Col==dungeonEscape_trap2Col || dungeonEscape_trap1Row==dungeonEscape_monster1Row || dungeonEscape_trap1Col==dungeonEscape_monster1Col);
	do{
		srand(time(0));
		dungeonEscape_monster2Row = rand()%9;
		srand(time(0));
		dungeonEscape_monster2Col = rand()%17;
	}while(dungeonEscape_monster2Row==1 || dungeonEscape_monster2Col==1 || dungeonEscape_dungeonMap[dungeonEscape_monster2Row][dungeonEscape_monster2Col]=='#' || dungeonEscape_dungeonMap[dungeonEscape_monster2Row][dungeonEscape_monster2Col]=='*' || dungeonEscape_monster2Row==dungeonEscape_trap2Row || dungeonEscape_monster2Col==dungeonEscape_trap2Col || dungeonEscape_trap1Row==dungeonEscape_monster2Row || dungeonEscape_trap1Col==dungeonEscape_monster2Col || dungeonEscape_monster1Row==dungeonEscape_monster2Row || dungeonEscape_monster2Col==dungeonEscape_monster1Col);
	return;
}

void dungeonEscape_printdungeonMap(){
	system("cls");
	for(int i=0;i<9;i++){
		for(int j=0;j<17;j++){
			if(dungeonEscape_alive == true && i==dungeonEscape_playerRow && j==dungeonEscape_playerCol){
				printf("@");
			}
			else if(dungeonEscape_alive == false && i==dungeonEscape_playerRow && j==dungeonEscape_playerCol){
				printf("X");
			}
			else if(i==dungeonEscape_monster1Row && j==dungeonEscape_monster1Col){
				printf("O");
			}
			else if(i==dungeonEscape_monster2Row && j==dungeonEscape_monster2Col){
				printf("O");
			}
			else printf("%c", dungeonEscape_dungeonMap[i][j]);
		}
		printf("\n");
	}
	return;
}
void dungeonEscape_input(){
	dungeonEscape_playerMove= 0;
	if(_kbhit()){
		switch (_getch()){
			case 'a':
				dungeonEscape_playerMove= 1;
				break;
			case 'd':
				dungeonEscape_playerMove= 2;
				break;
			case 'w':
				dungeonEscape_playerMove= 3;
				break;
			case 's':
				dungeonEscape_playerMove= 4;
				break;
			case 'A':
				dungeonEscape_playerMove= 1;
				break;
			case 'D':
				dungeonEscape_playerMove= 2;
				break;
			case 'W':
				dungeonEscape_playerMove= 3;
				break;
			case 'S':
				dungeonEscape_playerMove= 4;
				break;
		}
	}
	return;
}
void dungeonEscape_logic(){
	int dungeonEscape_flag = 1;
	if(dungeonEscape_playerMove== 1 && dungeonEscape_dungeonMap[dungeonEscape_playerRow][dungeonEscape_playerCol-1]=='#'){
		dungeonEscape_flag = 0;
	}
	else if(dungeonEscape_playerMove== 2 && dungeonEscape_dungeonMap[dungeonEscape_playerRow][dungeonEscape_playerCol+1]=='#'){
		dungeonEscape_flag = 0;
	}
	else if(dungeonEscape_playerMove== 3 && dungeonEscape_dungeonMap[dungeonEscape_playerRow-1][dungeonEscape_playerCol]=='#'){
		dungeonEscape_flag = 0;
	}
	else if(dungeonEscape_playerMove== 4 && dungeonEscape_dungeonMap[dungeonEscape_playerRow+1][dungeonEscape_playerCol]=='#'){
		dungeonEscape_flag = 0;
	}
	if(dungeonEscape_flag==0){
		return;
	}
	switch( dungeonEscape_playerMove){
		case 1:
			dungeonEscape_playerCol--;
			break;
		case 2:
			dungeonEscape_playerCol++;
			break;
		case 3:
			dungeonEscape_playerRow--;
			break;
		case 4:
			dungeonEscape_playerRow++;
			break;
	}
	if((dungeonEscape_playerRow==dungeonEscape_monster1Row && dungeonEscape_playerCol==dungeonEscape_monster1Col) || (dungeonEscape_playerRow==dungeonEscape_monster2Row && dungeonEscape_playerCol==dungeonEscape_monster2Col)|| (dungeonEscape_playerRow == dungeonEscape_trap1Row && dungeonEscape_playerCol==dungeonEscape_trap1Col) || (dungeonEscape_playerRow == dungeonEscape_trap2Row && dungeonEscape_playerCol==dungeonEscape_trap2Col)){
		dungeonEscape_alive = false;
	}
	else if(dungeonEscape_playerRow == 8 && dungeonEscape_playerCol == 14){
		dungeonEscape_win = true;
	}
	return;
}
void dungeonEscape_positionChange(int *dungeonEscape_monsterRow, int *dungeonEscape_monsterCol){
	int dungeonEscape_moveIndicator = rand()%5, dungeonEscape_moveMonster;
	if(dungeonEscape_moveIndicator == 0){
		int dungeonEscape_direction = rand()%4;
		switch(dungeonEscape_direction){
			case 0:
				dungeonEscape_moveMonster = 1;
				break;
			case 1:
				dungeonEscape_moveMonster = 2;
				break;
			case 2:
				dungeonEscape_moveMonster = 3;
				break;
			case 3:
				dungeonEscape_moveMonster = 4;
				break;
		}
		int dungeonEscape_flag = 1;
		if(dungeonEscape_moveMonster== 1 && (dungeonEscape_dungeonMap[*dungeonEscape_monsterRow][*dungeonEscape_monsterCol-1]=='#' || dungeonEscape_dungeonMap[*dungeonEscape_monsterRow][*dungeonEscape_monsterCol-1]=='*' || *dungeonEscape_monsterRow==dungeonEscape_trap2Row || *dungeonEscape_monsterCol-1==dungeonEscape_trap2Col || dungeonEscape_trap1Row==*dungeonEscape_monsterRow || dungeonEscape_trap1Col==*dungeonEscape_monsterCol-1)){
			dungeonEscape_flag = 0;
		}
		else if(dungeonEscape_moveMonster== 2 && (dungeonEscape_dungeonMap[*dungeonEscape_monsterRow][*dungeonEscape_monsterCol+1]=='#'|| dungeonEscape_dungeonMap[*dungeonEscape_monsterRow][*dungeonEscape_monsterCol+1]=='*' || *dungeonEscape_monsterRow==dungeonEscape_trap2Row || *dungeonEscape_monsterCol+1==dungeonEscape_trap2Col || dungeonEscape_trap1Row==*dungeonEscape_monsterRow || dungeonEscape_trap1Col==*dungeonEscape_monsterCol+1)){
			dungeonEscape_flag = 0;
		}
		else if(dungeonEscape_moveMonster== 3 && (dungeonEscape_dungeonMap[*dungeonEscape_monsterRow-1][*dungeonEscape_monsterCol]=='#' || dungeonEscape_dungeonMap[*dungeonEscape_monsterRow-1][*dungeonEscape_monsterCol]=='*' || *dungeonEscape_monsterRow-1==dungeonEscape_trap2Row || *dungeonEscape_monsterCol==dungeonEscape_trap2Col || dungeonEscape_trap1Row==*dungeonEscape_monsterRow-1 || dungeonEscape_trap1Col==*dungeonEscape_monsterCol)){
			dungeonEscape_flag = 0;
		}
		else if(dungeonEscape_moveMonster== 4 && (dungeonEscape_dungeonMap[*dungeonEscape_monsterRow+1][*dungeonEscape_monsterCol]=='#' || dungeonEscape_dungeonMap[*dungeonEscape_monsterRow+1][*dungeonEscape_monsterCol]=='*' || *dungeonEscape_monsterRow+1==dungeonEscape_trap2Row || *dungeonEscape_monsterCol==dungeonEscape_trap2Col || dungeonEscape_trap1Row==*dungeonEscape_monsterRow+1 || dungeonEscape_trap1Col==*dungeonEscape_monsterCol)){
			dungeonEscape_flag = 0;
		}
		if(dungeonEscape_flag==0){
			return;
		}
		switch(dungeonEscape_moveMonster){
			case 1:
				*dungeonEscape_monsterCol-=1;
				break;
			case 2:
				*dungeonEscape_monsterCol+=1;
				break;
			case 3:
				*dungeonEscape_monsterRow-=1;
				break;
			case 4:
				*dungeonEscape_monsterRow+=1;
				break;
		}
	}
}
void dungeonEscape_startgame(){
	dungeonEscape_setup();
	while(dungeonEscape_alive==true && dungeonEscape_win==false){
		dungeonEscape_printdungeonMap();
		dungeonEscape_input();
		dungeonEscape_logic();
		dungeonEscape_positionChange(&dungeonEscape_monster1Row, &dungeonEscape_monster1Col);
		dungeonEscape_positionChange(&dungeonEscape_monster2Row, &dungeonEscape_monster2Col);
		dungeonEscape_delay(1);
	}
	if(dungeonEscape_win==true){
		system("cls");
		dungeonEscape_printdungeonMap();
		printf("\n Congratulations! You reach the endpoint safely!\n\n");
	}
	else if(dungeonEscape_alive==false){
		system("cls");
		dungeonEscape_printdungeonMap();
		printf("\n You Died!\n");
	}
	getchar();
	printf(" Press Enter to Continue!");
	getchar();
}
void dungeonEscape_rules(){
	system("cls");
	printf(" How to play dungeon arcade one-O-one\n");
	printf(" ====================================\n");
	printf(" 1. Player have to reach the end point ('*') of the maze to win the game\n");
	printf(" 2. Player can use W(up), A(left), S(down), D(right) to move.\n");
	printf(" 3. Beware of hidden traps around the dungeon!\n");
	printf(" 4. Player can reveal hidden traps if they are within 2 tiles from the traps.\n");
	printf(" 5. Player will be defeated if they either hit the dungeon's monster ('O') or the dungeon's traps ('X')\n");
	printf(" 6. Monsters will keep moving while you stop. So keep moving and don't get caught!\n");
	getchar();
	printf(" Press enter to continue...");
	getchar();
	return;
}
void dungeonEscape_game(){
	int dungeonEscape_indexMap=0;
	FILE *fmap = fopen(".\\Dungeon Escape\\DungeonMap.txt", "r");
	while(fscanf(fmap, "%[^\n]\n", dungeonEscape_dungeonMap[dungeonEscape_indexMap])!=EOF){
		dungeonEscape_indexMap++;
	}
	fclose(fmap);
	char dungeonEscape_choice;
	do{
		do{
			system("cls");
			printf("  ______     __    __   __     __     _______   ________     _______     __     __\n");
			printf(" |   _  \\   |  |  |  | |   \\  |  |   / ______| |   _____|   /  ___  \\   |   \\  |  |\n");
			printf(" |  | \\  \\  |  |  |  | |    \\ |  |  / /  ____  |  |_____   /  /   \\  \\  |    \\ |  |\n");
			printf(" |  |  |  | |  |  |  | |  |\\ \\|  | | |  |__  | |   _____| |  |     |  | |  |\\ \\|  |\n");
			printf(" |  |_/  /  |  |__|  | |  | \\    |  \\ \\____| | |  |_____   \\  \\___/  /  |  | \\    |\n");
			printf(" |______/   |________| |__|  \\ __|   \\_______| |________|   \\_______/   |__|  \\ __|\n");
 			printf("\t		 ______  _____  _____          _____  ______ \n");
 			printf("\t		|  ____|/ ____|/ ____|   /\\   |  __ \\|  ____|\n");
		 	printf("\t 		| |__  | (___ | |       /  \\  | |__) | |__   \n");
 			printf("\t 		|  __|  \\___ \\| |      / /\\ \\ |  ___/|  __|  \n");
 			printf("\t 		| |____ ____) | |____ / ____ \\| |    | |____ \n");
 			printf("\t		|______|_____/ \\_____/_/    \\_\\_|    |______|\n");
			printf("\n\t\t\t\t\t1. Play\n");
			printf("\t\t\t\t\t2. Rules\n");
			printf("\t\t\t\t\t3. Exit\n");
			printf("\t\t\t\t\t>> ");
			dungeonEscape_choice = getch();
			printf("%c\n", dungeonEscape_choice);
		}while(dungeonEscape_choice-'0'<1 || dungeonEscape_choice-'0'>3);
		dungeonEscape_choice-='0';
		switch(dungeonEscape_choice){
			case 1:
				dungeonEscape_startgame();
				break;
			case 2:
				dungeonEscape_rules();
				break;
			case 3:
				break;
		}
	}while(dungeonEscape_choice!=3);
	return;
}
