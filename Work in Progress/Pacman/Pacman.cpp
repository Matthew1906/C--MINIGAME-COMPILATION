#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

char pacman_map[105][105];
int pacman_indexMap=0;

bool pacman_alive = true;
bool pacman_win = false;
int pacman_row, pacman_col, move=0, pacman_extra=0;

// 2-2 , 2-36 , 18-2, 18-36
struct pacman_fruit{
	int row;
	int col;
	bool eaten;
}fruits[4];
int pacman_food;//166
bool timer = false;

struct pacman_ghosts{
	int row;
	int col;
	int status; // 1 = chase, 2 = scatter, 3 = frightened
	char symbol;
	bool alive;
}ghosts[4];

void pacman_setup(){
	// read map
	pacman_indexMap = 0;
	FILE *fmap = fopen("..\\Pacman\\PacmanMap.txt", "r");
	while(fscanf(fmap, "%[^\n]\n", pacman_map[pacman_indexMap])!=EOF){
		pacman_indexMap++;
	}
	fclose(fmap);
	//initialize fruits
	fruits[0].row = 2;
	fruits[0].col = 2;
	fruits[1].row = 2;
	fruits[1].col = 36;
	fruits[2].row = 18;
	fruits[2].col = 2;
	fruits[3].row = 18;
	fruits[3].col = 36;
	for(int i=0;i<4;i++){
		fruits[i].eaten = false;
	}
	//initialize ghosts
	ghosts[0].row = 10;
	ghosts[0].col = 16;
	ghosts[0].symbol = 'B';
	ghosts[1].row = 10;
	ghosts[1].col = 18;
	ghosts[1].symbol = 'I';
	ghosts[2].row = 10;
	ghosts[2].col = 20;
	ghosts[2].symbol = 'P';
	ghosts[3].row = 10;
	ghosts[3].col = 22;
	ghosts[3].symbol = 'C';
	for(int i=0;i<4;i++){
		ghosts[i].status = 1;
		ghosts[i].alive = true;
	}
	//initialize player
	pacman_row = 17;
	pacman_col = 18;
	pacman_alive = true;
	pacman_win = false;
	pacman_food = 0;
	pacman_extra = 0;
	//fix map	
	for(int i=0;i<25;i++){
		for(int j=0;j<40;j++){
			if(pacman_map[i][j]=='/'){
				pacman_map[i][j]=' ';
			}
		}
	}
}

void pacman_printmap(){
	system("cls");
	for(int i=0;i<25;i++){
		for(int j=0;j<40;j++){
			//FRUITS
			if(i==fruits[0].row && j==fruits[0].col && fruits[0].eaten==false){
				printf("O");
			}
			else if(i==fruits[1].row && j==fruits[1].col && fruits[1].eaten==false){
				printf("O");
			}
			else if(i==fruits[2].row && j==fruits[2].col && fruits[2].eaten==false){
				printf("O");
			}
			else if(i==fruits[3].row && j==fruits[3].col && fruits[3].eaten==false){
				printf("O");
			}
			//GHOSTS
			else if(i==ghosts[0].row && j==ghosts[0].col){
				printf("%c", ghosts[0].symbol);
			}
			else if(i==ghosts[1].row && j==ghosts[1].col){
				printf("%c", ghosts[1].symbol);
			}
			else if(i==ghosts[2].row && j==ghosts[2].col){
				printf("%c", ghosts[2].symbol);
			}
			else if(i==ghosts[3].row && j==ghosts[3].col){
				printf("%c", ghosts[3].symbol);
			}
			//PLAYERS
			else if(i==pacman_row && j==pacman_col){
				printf("@");
			}
			else{
				printf("%c", pacman_map[i][j]);
			}
		}
		printf("\n");
	}
	printf("Points: %d\n", pacman_food+pacman_extra);
}

void pacman_input(){
	move = 0;
	if(_kbhit()){
		switch(_getch()){
			case 'a':
				move = 1;
				break;
			case 's':
				move = 3;
				break;
			case 'd':
				move = 2;
				break;
			case 'w':
				move = 4;
				break;
		}
	}
}

void pacman_logic(){
	// validation of movement
	int flag = 0;
	if(move==1 && pacman_map[pacman_row][pacman_col-2]!='#'){
		flag = 1;
	}
	else if(move==2 && pacman_map[pacman_row][pacman_col+2]!='#'){
		flag = 1;
	}
	else if(move==3 && pacman_map[pacman_row+1][pacman_col]!='#'){
		flag = 1;
	}
	else if(move==4 && pacman_map[pacman_row-1][pacman_col]!='#'){
		flag = 1;
	}
	//movement
	if(flag==1){
		switch(move){
			case 1:
				pacman_col-=2;
				break;
			case 2:
				pacman_col+=2;
				break;
			case 3:
				pacman_row++;
				break;
			case 4:
				pacman_row--;
				break;
		}
	}
	// eat food
	if(pacman_map[pacman_row][pacman_col]=='.'){
		pacman_map[pacman_row][pacman_col]=' ';
		pacman_food++;
	}
	//left-right gate
	if(pacman_row==10 && pacman_col<=0){
		pacman_col = 38;
	}
	else if(pacman_row==10 && pacman_col>=38){
		pacman_col = 0;
	}
	//win condition
	if(pacman_food==166){
		pacman_win= true;
	}
	//timer for frightened mode / eat power pill
	if(pacman_row== fruits[0].row && pacman_col==fruits[0].col){
		fruits[0].eaten = true;
		timer  = true;
	}
	else if(pacman_row== fruits[1].row && pacman_col==fruits[1].col){
		fruits[1].eaten = true;
		timer = true;
	}
	else if(pacman_row== fruits[2].row && pacman_col==fruits[2].col){
		fruits[2].eaten = true;
		timer = true;
	}
	else if(pacman_row== fruits[3].row && pacman_col==fruits[3].col){
		fruits[3].eaten = true;
		timer = true;
	}
	// CHASE / PATROL MODE
	if(pacman_row == ghosts[0].row && pacman_col == ghosts[0].col && ghosts[0].status!=3){
		pacman_alive = false;
	}
	else if(pacman_row == ghosts[1].row && pacman_col == ghosts[1].col && ghosts[1].status!=3){
		pacman_alive = false;
	}
	else if(pacman_row == ghosts[2].row && pacman_col == ghosts[2].col && ghosts[2].status!=3){
		pacman_alive = false;
	}
	else if(pacman_row == ghosts[3].row && pacman_col == ghosts[3].col && ghosts[3].status!=3){
		pacman_alive = false;
	}
	// FRIGHTENED MODE
	if(pacman_row == ghosts[0].row && pacman_col == ghosts[0].col && ghosts[0].status==3){
		pacman_extra+=100;
		ghosts[0].row = 10;
		ghosts[0].col = 16;
		ghosts[0].alive = false;
	}
	else if(pacman_row == ghosts[1].row && pacman_col == ghosts[1].col && ghosts[1].status==3){
		pacman_extra+=100;
		ghosts[1].row = 10;
		ghosts[1].col = 18;
		ghosts[1].alive = false;
	}
	else if(pacman_row == ghosts[2].row && pacman_col == ghosts[2].col && ghosts[2].status==3){
		pacman_extra+=100;
		ghosts[2].row = 10;
		ghosts[2].col = 20;
		ghosts[2].alive = false;
	}
	else if(pacman_row == ghosts[3].row && pacman_col == ghosts[3].col && ghosts[3].status==3){
		pacman_extra+=100;
		ghosts[3].row = 10;
		ghosts[3].col = 22;
		ghosts[3].alive = false;
	}
}

void pacman_Blinky(){
	
}

void pacman_Pinky(){
	
}

void pacman_Inky(){
	
}

void pacman_Clyde(){
	
}

void pacman_delay(double numsec){
	clock_t start = clock();
	while(clock()< start+100*numsec);
}

void pacman_startgame(){
	getch();
	pacman_setup();
	pacman_input();
	pacman_logic();
	int turn=0,end=0,endGhosts[4]={0};
	while(pacman_alive==true && pacman_win==false){
		if(turn==end){
			end = 0;
			for(int i=0;i<4;i++){
				ghosts[i].status = 1;
			}
		}
		if(endGhosts[0]==timer){
			ghosts[0].alive = true;
			endGhosts[0]=0;
		}
		if(endGhosts[1]==timer){
			ghosts[1].alive = true;
			endGhosts[1]=0;
		}
		if(endGhosts[2]==timer){
			ghosts[2].alive = true;
			endGhosts[2]=0;
		}
		if(endGhosts[3]==timer){
			ghosts[3].alive = true;
			endGhosts[3]=0;
		}
		pacman_printmap();
		pacman_input();
		pacman_logic();
		if(timer == true){
			timer = false;
			end = turn+20;
			for(int i=0;i<4;i++){
				ghosts[i].status = 3;
			}
		}
		//red = aggressive, upper right 
		if(ghosts[0].alive==false){
			endGhosts[0]= turn+20;
		}else pacman_Blinky();
		//pink = flank, upper left
		if(ghosts[1].alive==false){
			endGhosts[1]= turn+20;
		}else pacman_Pinky();
		//cyan = patrol, lower right
		if(ghosts[2].alive==false){
			endGhosts[2]= turn+20;
		}else pacman_Inky();
		//orange = random, lower left
		if(ghosts[3].alive==false){
			endGhosts[3]= turn+20;
		}else pacman_Clyde(); 
		pacman_delay(1);
		turn++;
		//break;
	}
	if(pacman_alive==false){
		printf("You Lose!\n");
	}
	else if(pacman_win==true){
		printf("You Win!\n");
	}
	printf("Press enter to continue..");
	getchar();
	return;
}

void pacman_htp(){
	return;
}

int main (){
	char choice;
	do{
		do{
			system("cls");
			printf("1. Start Game\n");
			printf("2. How to Play\n");
			printf("3. Exit\n");
			printf(">> ");
			choice = getchar();
			//getchar();
		}while(choice-'0'<1 || choice-'0'>3);
		switch(choice-'0'){
			case 1:
				pacman_startgame();
				break;
			case 2:
				pacman_htp();
				break;
			case 3: 
				break;
		}
	}while(choice-'0'!=3);
	return 0;
}
