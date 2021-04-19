#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define DOWN 80
#define UP 72
#define RIGHT 77
#define LEFT 75
#define ENTER 13

void tictactoe_logo(){
	printf("		_______  ___   _______    _______  _______  _______    _______  _______  _______ \n");
	printf("		|       ||   | |       |  |       ||   _   ||       |  |       ||       ||       |\n");
	printf("		|_     _||   | |       |  |_     _||  |_|  ||       |  |_     _||   _   ||    ___|\n");
	printf("		  |   |  |   | |       |    |   |  |       ||       |    |   |  |  | |  ||   |___ \n");
	printf("		  |   |  |   | |      _|    |   |  |       ||      _|    |   |  |  |_|  ||    ___|\n");
	printf("		  |   |  |   | |     |_     |   |  |   _   ||     |_     |   |  |       ||   |___ \n");
	printf("		  |___|  |___| |_______|    |___|  |__| |__||_______|    |___|  |_______||_______|\n\n");
	printf("						____________\n");
	printf("						|   |   |   |\n");
	printf("						| X | O | X |\n");
	printf("						|___|___|___|\n");
	printf("						|   |   |   |\n");
	printf("						| O | X | O |\n");
	printf("						|___|___|___|\n");
	printf("						|   |   |   |\n");
	printf("						| X | O | X |\n");
	printf("						|___|___|___|\n\n");
}
int tictactoe_row=2, tictactoe_col=2;
// coordinates (2,2), (2,6), (2,10), (5,2), (5,6), (5,10), (8,2), (8,6), (8,10) 
void tictactoe_printboard(char board[10][100]){
	for(int a=0;a<10;a++){
		printf("\t\t\t\t\t%s\n", board[a]);
	}
}
int tictactoe_check(char board[10][100]){
	for(int row = 2;row<=8;row+=3){
		for(int col=2;col<=10;col+=4){
			if(board[row][col]==' '){
				return 1;
			}
		}
	}
	return -1;
}
int tictactoe_wincondition(char board[10][100], char p){
	//horizontal
	if(board[2][2]== p && board[2][6]== p && board[2][10]==p)return 1;
	else if(board[5][2]== p && board[5][6]== p && board[5][10]==p)return 1;
	else if(board[8][3]== p && board[8][6]== p && board[8][10]==p)return 1;
	//vertical
	else if(board[2][2]== p && board[5][2]== p && board[8][2]==p)return 1;
	else if(board[2][6]== p && board[5][6]== p && board[8][6]==p)return 1;
	else if(board[2][10]== p && board[6][10]== p && board[8][10]==p)return 1;
	//diagonal
	else if(board[2][2]== p && board[5][6]== p && board[8][10]==p)return 1;
	else if(board[8][2]== p && board[5][6]== p && board[2][10]==p)return 1;
	//tie
//	else if(board[2][2]!=' '&& board[2][6]!= ' ' && board[2][10]!=' ' && board[5][2]!=' '&& board[5][6]!= ' ' && board[5][10]!=' ' && board[8][2]!=' '&& board[8][6]!= ' ' && board[8][10]!=' ' )return 2;
	else return -1;
}
void tictactoe_resetboard(int *tictactoe_row, int *tictactoe_col, char board[10][100]){
		if(board[2][2]==' '){
			*tictactoe_row=2;
			*tictactoe_col=2;
		}
		else if(board[2][6]==' '){
			*tictactoe_row=2;
			*tictactoe_col=6;
		}
		else if(board[2][10]==' '){
			*tictactoe_row=2;
			*tictactoe_col=10;
		}
		else if(board[5][2]==' '){
			*tictactoe_row=5;
			*tictactoe_col=2;
		}
		else if(board[5][6]==' '){
			*tictactoe_row=5;
			*tictactoe_col=6;
		}
		else if(board[5][10]==' '){
			*tictactoe_row=5;
			*tictactoe_col=10;
		}
		else if(board[8][2]==' '){
			*tictactoe_row=8;
			*tictactoe_col=2;
		}
		else if(board[8][6]==' '){
			*tictactoe_row=8;
			*tictactoe_col=6;
		}
		else if(board[8][10]==' '){
			*tictactoe_row=8;
			*tictactoe_col=10;
		}		
		board[*tictactoe_row][*tictactoe_col]='*';
		return;
}
void tictactoe_controls(char board[10][100], int *tictactoe_row, int *tictactoe_col, char p, char *player){
		char key;
		while(key!=ENTER){
			key=getch();
		 	if(key==DOWN && *tictactoe_row<=8){
				system("cls");
				printf("\t\t\t\t\tIt's %s's turn!\n", player);
				board[*tictactoe_row][*tictactoe_col]=' ';
				if(board[*tictactoe_row+3][*tictactoe_col]!=' ' && board[*tictactoe_row+6][*tictactoe_col]==' '){
					*tictactoe_row+=6;
				}
				else if(board[*tictactoe_row+3][*tictactoe_col]==' '){
					*tictactoe_row+=3;
				}
				else if(board[*tictactoe_row+3][*tictactoe_col]!=' '&& board[*tictactoe_row+6][*tictactoe_col]!=' '){
					if(board[*tictactoe_row+3][*tictactoe_col+8]==' '){
						*tictactoe_row+=3, *tictactoe_col+=8;
					}
					else if(board[*tictactoe_row+3][*tictactoe_col-8]==' '){
						*tictactoe_row+=3, *tictactoe_col-=8;
					}
					else if(board[*tictactoe_row+6][*tictactoe_col+8]==' '){
						*tictactoe_row+=6; *tictactoe_col+=8;
					}
					else if(board[*tictactoe_row+6][*tictactoe_col-8]==' '){
						*tictactoe_row+=6, *tictactoe_col-=8;
					}
				}
				board[*tictactoe_row][*tictactoe_col]='*';
				tictactoe_printboard(board);
			}
			else if(key==UP && *tictactoe_row>=2){
				system("cls");
				printf("\t\t\t\t\tIt's %s's turn!\n", player);
				board[*tictactoe_row][*tictactoe_col]=' ';
				if(board[*tictactoe_row-3][*tictactoe_col]!=' ' && board[*tictactoe_row-6][*tictactoe_col]==' '){
					*tictactoe_row-=6;
				}
				else if(board[*tictactoe_row-3][*tictactoe_col]==' ')*tictactoe_row-=3;
				else if(board[*tictactoe_row-3][*tictactoe_col]!=' '&& board[*tictactoe_row-6][*tictactoe_col]!=' '){
					if(board[*tictactoe_row-3][*tictactoe_col+8]==' '){
						*tictactoe_row-=3, *tictactoe_col+=8;
					}
					else if(board[*tictactoe_row-3][*tictactoe_col-8]==' '){
						*tictactoe_row-=3, *tictactoe_col-=8;
					}
					else if(board[*tictactoe_row-6][*tictactoe_col+8]==' '){
						*tictactoe_row-=6; *tictactoe_col+=8;
					}
					else if(board[*tictactoe_row-6][*tictactoe_col-8]==' '){
						*tictactoe_row-=6, *tictactoe_col-=8;
					}
				}
				board[*tictactoe_row][*tictactoe_col]='*';
				tictactoe_printboard(board);
			}
			else if(key==LEFT && *tictactoe_col>=2){
				system("cls");
				printf("\t\t\t\t\tIt's %s's turn!\n", player);
				board[*tictactoe_row][*tictactoe_col]=' ';
				if(board[*tictactoe_row][*tictactoe_col-4]!=' '&& board[*tictactoe_row][*tictactoe_col-8]==' ')*tictactoe_col-=8;
				else if(board[*tictactoe_row][*tictactoe_col-4]==' ')*tictactoe_col-=4;
				else if(board[*tictactoe_row][*tictactoe_col-4]!=' '&&board[*tictactoe_row][*tictactoe_col-8]!=' '){
					if(board[*tictactoe_row+3][*tictactoe_col-4]==' '){
						*tictactoe_row+=3,*tictactoe_col-=4;
					}
					else if(board[*tictactoe_row-3][*tictactoe_col-4]==' '){
						*tictactoe_row-=3, *tictactoe_col-=4;
					}
					else if(board[*tictactoe_row-6][*tictactoe_col-8]==' '){
						*tictactoe_row-=6, *tictactoe_col-=8;
					}
					else if(board[*tictactoe_row+6][*tictactoe_col-8]==' '){
						*tictactoe_row+=6, *tictactoe_col-=8;
					}
				}
				board[*tictactoe_row][*tictactoe_col]='*';
				tictactoe_printboard(board);
			}
			else if(key==RIGHT && *tictactoe_col<=10){
				system("cls");
				printf("\t\t\t\t\tIt's %s's turn!\n", player);
				board[*tictactoe_row][*tictactoe_col]=' ';
				if(board[*tictactoe_row][*tictactoe_col+4]!=' '&& board[*tictactoe_row][*tictactoe_col+8]==' ')*tictactoe_col+=8;
				else if(board[*tictactoe_row][*tictactoe_col+4]==' ')*tictactoe_col+=4;
				else if(board[*tictactoe_row][*tictactoe_col+4]!=' '&&board[*tictactoe_row][*tictactoe_col+8]!=' '){
					if(board[*tictactoe_row+3][*tictactoe_col+4]==' '){
						*tictactoe_row+=3,*tictactoe_col+=4;
					}
					else if(board[*tictactoe_row-3][*tictactoe_col+4]==' '){
						*tictactoe_row-=3, *tictactoe_col+=4;
					}
					else if(board[*tictactoe_row-6][*tictactoe_col+8]==' '){
						*tictactoe_row-=6, *tictactoe_col+=8;
					}
					else if(board[*tictactoe_row+6][*tictactoe_col+8]==' '){
						*tictactoe_row+=6, *tictactoe_col+=8;
					}
				}
				board[*tictactoe_row][*tictactoe_col]='*';
				tictactoe_printboard(board);
			}
		
		}
		system("cls");
		board[*tictactoe_row][*tictactoe_col]= p;
		return;
}

void tictactoe_startgame(){
	char board[10][100]= {
		"____________",
		"|   |   |   |",
		"|   |   |   |",
		"|___|___|___|",
		"|   |   |   |",
		"|   |   |   |",
		"|___|___|___|",
		"|   |   |   |",
		"|   |   |   |",
		"|___|___|___|"
	};
	tictactoe_logo();
	char player1[105], player2[105], p1, p2;
	//Player 1
	printf("\t\t\t\t\tPlayer 1: ");
	scanf("%[^\n]", player1);
	getchar();
	printf("\t\t\t\t\tDo you want to use \'X\' or \'O\'?\n");
	do{
		printf("\t\t\t\t\tEnter your choice! : ");
		scanf("%c", &p1);
		if(p1!='X'&& p1!='O'){
			printf("\t\t\t\t\tYou can only choose \'X\' or \'O\'!\n");
			getchar();
		}
	}while(p1!='X'&& p1!='O');
	//Player 2
	getchar();
	printf("\t\t\t\t\tPlayer 2: ");
	scanf("%[^\n]", player2);
	getchar();
	if(p1 =='X')p2 ='O';
	else p2 ='X';
	int win1 = tictactoe_wincondition(board, p1), win2 = tictactoe_wincondition(board, p2);
	board[tictactoe_row][tictactoe_col]='*';
	tictactoe_printboard(board);
	int cek = tictactoe_check(board);
	while(win2==-1 && win1==-1 && cek==1){
		tictactoe_controls(board, &tictactoe_row, &tictactoe_col, p1, player1);
		win1 = tictactoe_wincondition(board, p1);
		cek = tictactoe_check(board);
		if(cek==-1 || win1==1 )break;
//		system("cls");
		tictactoe_resetboard(&tictactoe_row, &tictactoe_col, board);
		tictactoe_printboard(board);
		tictactoe_controls(board, &tictactoe_row, &tictactoe_col, p2, player2);
//		system("cls");
		win2= tictactoe_wincondition(board, p2);
		cek = tictactoe_check(board);
		if(cek==-1 || win2==1 )break;
		tictactoe_resetboard(&tictactoe_row, &tictactoe_col, board);
		tictactoe_printboard(board);
	}
	if(win1==1)printf("\t\t\t\t\tPlayer 1 wins!!\n");
	else if(win2==1)printf("\t\t\t\t\tPlayer 2 wins!!\n");
	else if(cek=-1)printf("\t\t\t\t\tIt's a Tie!!\n");
	tictactoe_printboard(board);
	getchar();
	printf(" Press Enter to Continue!");
	getchar();
	system("cls");
	return;
}

void tictactoe_htp(){
	printf(" Tic tac toe is a two player game that results in players using a circle or cross symbol which can be used on a 9x9 board.\n");
	printf(" The rules:\n");
	printf(" - Players can choose between a circle and a cross symbol\n");
	printf(" - Players can use the arrow key to make a move, i.e place their symbol on the square\n");
	printf(" - If a player places their symbol, either diagonally or in a straight line, 3 in a row then they are the winner\n");
	printf(" - If no player has won and all the squares are used then a tie is formed\n");
	getchar();
	printf(" Press Enter to Continue!");
	getchar();
	return;
}
void tictactoe_game(){
	char tictactoe_choice;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   	const SMALL_RECT WinSize = {0,0,125,20};
    SetConsoleWindowInfo( hConsole, true, &WinSize);
	do{
		do{
			system("cls");
			tictactoe_logo();
			printf("\t\t\t\t\t\t1. Play Game\n");
			printf("\t\t\t\t\t\t2. How to Play\n");
			printf("\t\t\t\t\t\t3. Exit\n");
			printf("\t\t\t\t\t\t>> ");
			tictactoe_choice = getchar();
			getchar();
		}while(tictactoe_choice-'0'<1|| tictactoe_choice-'0'>3);
		switch(tictactoe_choice-'0'){
			case 1:
				system("cls");
				tictactoe_startgame();
				break;
			case 2:
				system("cls");
				tictactoe_htp();
				break;
			case 3:
				break;
		}
	}while(tictactoe_choice-'0'!=3);
}
