#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

// ASCII ART FOR minesweeper_LOGO
const char minesweeper_LOGO[10][100] = {
	" ___ ___  ____  ____     ___  _____ __    __    ___    ___  ____   ___  ____", 
	"|   |   ||    ||    \\   /  _]/ ___/|  |__|  |  /  _]  /  _]|    \\ /  _]|    \\",
	"| _   _ | |  | |  _  | /  [_(   \\_ |  |  |  | /  [_  /  [_ |  o  )  [_ |  D  )",
	"|  \\_/  | |  | |  |  ||    _]\\__  ||  |  |  ||    _]|    _]|   _/    _]|    /",
	"|   |   | |  | |  |  ||   [_ /  \\ ||  `  '  ||   [_ |   [_ |  | |   [_ |    \\",
	"|   |   | |  | |  |  ||     |\\    | \\      / |     ||     ||  | |     ||  .  \\",
	"|___|___||____||__|__||_____| \\___|  \\_/\\_/  |_____||_____||__| |_____||__|\\_|"
};

const char minesweeper_DIFFICULTIES[10][100] = {
	"     ___ _  __  __ _            _ _   _     ",      
   	"    /   (_)/ _|/ _(_) ___ _   _| | |_(_) ___  ___", 
  	"   / /\\ / | |_| |_| |/ __| | | | | __| |/ _ \\/ __|",
 	"  / /_/ | |  _|  _| | (__| |_| | | |_| |  __/\\__ \\",
	" /___,' |_|_| |_| |_|\\___|\\__,_|_|\\__|_|\\___||___/"
};

const char minesweeper_WIN[10][100] = {
	" __   __  _______  __   __    _     _  ___   __    _ ",
	"|  | |  ||       ||  | |  |  | | _ | ||   | |  |  | |",
	"|  |_|  ||   _   ||  | |  |  | || || ||   | |   |_| |",
	"|       ||  | |  ||  |_|  |  |       ||   | |       |",
	"|_     _||  |_|  ||       |  |       ||   | |  _    |",
	"  |   |  |       ||       |  |   _   ||   | | | |   |",
	"  |___|  |_______||_______|  |__| |__||___| |_|  |__|"
};

const char minesweeper_LOSE[10][100] = {
	" __   __  _______  __   __    ___      _______  _______  _______ ",
	"|  | |  ||       ||  | |  |  |   |    |       ||       ||       |",
	"|  |_|  ||   _   ||  | |  |  |   |    |   _   ||  _____||    ___|",
	"|       ||  | |  ||  |_|  |  |   |    |  | |  || |_____ |   |___ ",
	"|_     _||  |_|  ||       |  |   |___ |  |_|  ||_____  ||    ___|",
	"  |   |  |       ||       |  |       ||       | _____| ||   |___ ",
	"  |___|  |_______||_______|  |_______||_______||_______||_______|"
};


const char minesweeper_END[10][100] = {
	" _______  __   __  _______  __    _  ___   _  __   __  _______  __   __ ",
	"|       ||  | |  ||   _   ||  |  | ||   | | ||  | |  ||       ||  | |  |",
	"|_     _||  |_|  ||  |_|  ||   |_| ||   |_| ||  |_|  ||   _   ||  | |  |",
	"  |   |  |       ||       ||       ||      _||       ||  | |  ||  |_|  |",
	"  |   |  |       ||       ||  _    ||     |_ |_     _||  |_|  ||       |",
	"  |   |  |   _   ||   _   || | |   ||    _  |  |   |  |       ||       |",
	"  |___|  |__| |__||__| |__||_|  |__||___| |_|  |___|  |_______||_______|"
};


// CONSOLE MANIPULATION
HANDLE minesweeper_Console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD minesweeper_CursorPosition;

void minesweeper_gotoXY(int x, int y){
	minesweeper_CursorPosition.X = x;
	minesweeper_CursorPosition.Y = y;
	SetConsoleCursorPosition(minesweeper_Console, minesweeper_CursorPosition);
}

// MAP VARIABLES AND FUNCTIONS
char minesweeper_ValueMap[50][50], minesweeper_RealMap[50][50];
int minesweeper_RowSize, minesweeper_ColSize, minesweeper_Mines;

void minesweeper_printRealMap(){
	for(int i =3;i<10;++i){
		minesweeper_gotoXY(minesweeper_ColSize,i);
		printf("%s", minesweeper_LOGO[i-3]);
	}
	minesweeper_gotoXY(4,13);
	for(int a=1;a<=minesweeper_ColSize;++a){
		printf("%02d ", a);
	}
	for(int i=0;i<minesweeper_RowSize;++i){
		minesweeper_gotoXY(1,14+i);
		printf("%02d ", i+1);
		minesweeper_gotoXY(4,14+i);
		for(int j=0;j<minesweeper_ColSize;++j){
			printf("%c  ", minesweeper_RealMap[i][j]);
		}
		printf("\n");
	}
}

// Easy -> 10 x 8 => 10
// Medium -> 20 x 16 =>40
// Hard -> 32 x 25 => 100

// GAMEPLAY 
int minesweeper_chooseDifficulty(){
	system("cls");
	int diff = 1;
	minesweeper_gotoXY(37,8+diff);
	printf(">> ");
	while(true){
		for(int i =3;i<8;++i){
			minesweeper_gotoXY(26,i);
			printf("%s", minesweeper_DIFFICULTIES[i-3]);
		}
		minesweeper_gotoXY(40,9);
		printf("Easy (8 x 10 | 10 mines)");
		minesweeper_gotoXY(40,10);
		printf("Medium (16 x 20 | 40 mines)");
		minesweeper_gotoXY(40,11);
		printf("Hard (25 x 32 | 100 mines)");
		minesweeper_gotoXY(40,12);
		printf("Go Back");
		minesweeper_gotoXY(25,14);
		printf("<< Use Arrow Up and Down to navigate between difficulties >>");
		minesweeper_gotoXY(35,15);
		printf("<< Press SPACE to choose!>>");
		system("pause>nul");
		if(GetAsyncKeyState(VK_UP)<0){
			minesweeper_gotoXY(37,8+diff);
			printf("   ");
			diff--;
			if(diff<1){
				diff = 4;
			}
			minesweeper_gotoXY(37,8+diff);
			printf(">> ");
		}
		if(GetAsyncKeyState(VK_DOWN)<0){
			minesweeper_gotoXY(37,8+diff);
			printf("   ");
			diff++;
			if(diff>4){
				diff = 1;
			}
			minesweeper_gotoXY(37,8+diff);
			printf(">> ");
		}
		if(GetAsyncKeyState(VK_SPACE)<0){
			return diff;
		}
	}
}

int minesweeper_countMines(int row, int col){
	int ctr = 0, moveX[3] = {-1,0,1}, moveY[3] = {-1,0,1};
	for(int i =0;i<3;++i){
		for(int j=0;j<3;++j){
			if(row+moveX[i]>=0 && row+moveX[i]<minesweeper_RowSize && col+moveY[j]>=0 && col+moveY[j]<minesweeper_ColSize){
				if(minesweeper_ValueMap[row+moveX[i]][col+moveY[j]]=='X'){
					ctr++;
				}
			}
		}
	}
	return ctr;
}

void minesweeper_init(){
	// choose difficulty
	switch(minesweeper_chooseDifficulty()){
		case 1:
			minesweeper_RowSize = 8, minesweeper_ColSize = 10, minesweeper_Mines = 10;
			break;
		case 2:
			minesweeper_RowSize = 16, minesweeper_ColSize = 20, minesweeper_Mines = 40;
			break;
		case 3:
			minesweeper_RowSize = 25, minesweeper_ColSize = 32, minesweeper_Mines = 100;
			break;
		case 4:
			minesweeper_RowSize = 0, minesweeper_ColSize = 0, minesweeper_Mines = 0;
			break;
	}
	system("cls");
	// initialize the map
	for(int i =0;i<minesweeper_RowSize;++i){
		for(int j=0;j<minesweeper_ColSize;++j){
			minesweeper_RealMap[i][j] = 254;
			minesweeper_ValueMap[i][j] = 'e';
		}
	}
	// randomize the mines
	srand(time(0));
	for(int i =0;i<minesweeper_Mines;++i){
		int row,col;
		do{
			row = rand()%minesweeper_RowSize;
			col = rand()%minesweeper_ColSize;
		}while(minesweeper_ValueMap[row][col]!='e');
		minesweeper_ValueMap[row][col] = 'X';
	}
	// set the value of each tile
	for(int i =0;i<minesweeper_RowSize;++i){
		for(int j=0;j<minesweeper_ColSize;++j){
			if(minesweeper_ValueMap[i][j]!='X'){
				int value = minesweeper_countMines(i, j);
				if(value>0){
					minesweeper_ValueMap[i][j] = value+'0';
				}
			}
		}
	}
}

void minesweeper_openPath(int row, int col){
	if(row<0 || row>=minesweeper_RowSize || col<0 || col>=minesweeper_ColSize || minesweeper_ValueMap[row][col]!='e'){
		return;
	}
	if(minesweeper_ValueMap[row][col]=='e'){
		minesweeper_RealMap[row][col] = ' ';
		minesweeper_ValueMap[row][col] = 'E';
	}
	minesweeper_openPath(row-1,col-1);
	minesweeper_openPath(row-1,col);
	minesweeper_openPath(row-1,col+1);
	minesweeper_openPath(row,col-1);
	minesweeper_openPath(row,col+1);
	minesweeper_openPath(row+1,col-1);
	minesweeper_openPath(row+1,col);
	minesweeper_openPath(row+1,col+1);
	return;
}

void minesweeper_playgame(){
	minesweeper_init();
	if(minesweeper_RowSize ==0){
		return;
	}
	bool win = false, lost = false;
	int flag = minesweeper_Mines, disarmed = 0;
	while(!win && !lost){
		system("cls");
		minesweeper_printRealMap();
		minesweeper_gotoXY(3*minesweeper_ColSize+5, 12+minesweeper_RowSize/2);
		printf("Flags left : %d", flag);
		minesweeper_gotoXY(3*minesweeper_ColSize+5, 14+minesweeper_RowSize/2);
		int row, col;
		printf("Input row(A) and column(B) [A B]: ");
		scanf("%d %d", &row, &col);
		getchar();
		if(row<1 || row>minesweeper_RowSize || col<1 || col>minesweeper_ColSize){
			continue;
		}
		char order[25] = "";
		minesweeper_gotoXY(3*minesweeper_ColSize+5, 16+minesweeper_RowSize/2);
		printf("Input Order (Dig | Flag)[case insensitive]: ");
		scanf("%[^\n]", order);
		getchar();
		if(strcmpi(order,"Dig")!=0 && strcmpi(order,"flag")!=0){
			continue;
		}
		row--, col--;
		if(strcmpi(order,"flag")==0){
			if(minesweeper_RealMap[row][col]==char(254) && flag>0){
				minesweeper_RealMap[row][col] = 'F';
				if(minesweeper_ValueMap[row][col]=='X'){
					disarmed++;
				}
				flag--;
			}
			else if (minesweeper_RealMap[row][col]=='F'){
				minesweeper_RealMap[row][col] = 254;
				if(minesweeper_ValueMap[row][col]=='X'){
					disarmed--;
				}
				flag++;
			}	
		}
		else if(strcmpi(order,"dig")==0 && minesweeper_RealMap[row][col]!='F'){
			if(minesweeper_ValueMap[row][col]=='X'){
				lost = true;
			}
			else if(minesweeper_ValueMap[row][col]=='e'){
				minesweeper_openPath(row,col);
			}
			else if(minesweeper_ValueMap[row][col]!='E'){
				minesweeper_RealMap[row][col] = minesweeper_ValueMap[row][col];
			}
		}
		if(disarmed==minesweeper_Mines){
			win = true;
		}
	}
	system("cls");
	if(win){
		for(int i = 3;i<10;++i){
			minesweeper_gotoXY(10,i);
			printf("%s",minesweeper_WIN[i-3]);
		}
		minesweeper_gotoXY(minesweeper_ColSize,12);
		printf("Press enter to continue..");
		getchar();
	}
	else{
		for(int i = 3;i<10;++i){
			minesweeper_gotoXY(10,i);
			printf("%s",minesweeper_LOSE[i-3]);
		}
		minesweeper_gotoXY(minesweeper_ColSize,12);
		printf("Press enter to continue..");
		getchar();
	}
	system("cls");
}


void minesweeper_htp(){
	system("cls");
	minesweeper_gotoXY(0,0);
	printf("\n\n  Minesweeper is a classic game where the player is tasked to flag all mines at a field, and digging the safe land.\n");
	printf("  When you dig on an empty plot, it will reveal all other adjacent empty plots.\n");
	printf("  When you dig on a numbered plot, it will reveal how many mines are there around the numbered plot.\n");
	printf("  When you found a landmine, flag them so that no one will go kaboom!\n");
	printf("  Make sure to flag the right plot, since you have limited flags.\n");
	printf("  You win when all the mines have been flagged, and lose if you accidentally dig on a plot with a landmine.\n\n");
	printf("  Have fun!\n\n");
	printf("  Press enter to continue...");
	getchar();
	system("cls");
}

void minesweeper_game(){
	system("cls");
	bool running = true;
	const SMALL_RECT WinSize = {0,0,100,20};
    SetConsoleWindowInfo(minesweeper_Console, true, &WinSize);
	int menu = 1;
	minesweeper_gotoXY(37,11+menu);
	printf(">> ");
	while(running){
		for(int i =3;i<10;++i){
			minesweeper_gotoXY(10,i);
			printf("%s", minesweeper_LOGO[i-3]);
		}
		minesweeper_gotoXY(40,12);
		printf("Start Game");
		minesweeper_gotoXY(40,13);
		printf("About Game");
		minesweeper_gotoXY(40,14);
		printf("Exit");
		minesweeper_gotoXY(25,16);
		printf("<< Use Arrow Up and Down to navigate between menus >>");
		minesweeper_gotoXY(35,17);
		printf("<< Press SPACE to choose!>>");
		system("pause>nul");
		if(GetAsyncKeyState(VK_UP)<0){
			minesweeper_gotoXY(37,11+menu);
			printf("   ");
			menu--;
			if(menu<1){
				menu = 3;
			}
			minesweeper_gotoXY(37,11+menu);
			printf(">> ");
		}
		if(GetAsyncKeyState(VK_DOWN)<0){
			minesweeper_gotoXY(37,11+menu);
			printf("   ");
			menu++;
			if(menu>3){
				menu = 1;
			}
			minesweeper_gotoXY(37,11+menu);
			printf(">> ");
		}
		if(GetAsyncKeyState(VK_SPACE)<0){
			switch(menu){
				case 1:
					minesweeper_playgame();
					menu = 1;
					minesweeper_gotoXY(37,11+menu);
					printf(">> ");
					break;
				case 2:
					minesweeper_htp();
					menu = 1;
					minesweeper_gotoXY(37,11+menu);
					printf(">> ");
					break;
				case 3:
					for(int i = 3;i<10;++i){
						minesweeper_gotoXY(10,i);
						printf("%s",minesweeper_END[i-3]);
					}
					getchar();
					running = false;	
					break;
			}
		}
	}
	return;
}
